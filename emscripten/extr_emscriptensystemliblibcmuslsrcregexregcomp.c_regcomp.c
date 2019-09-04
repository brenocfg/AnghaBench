#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {size_t state_id; struct TYPE_25__* state; int /*<<< orphan*/  assertions; int /*<<< orphan*/ * tags; } ;
typedef  TYPE_2__ tre_tnfa_transition_t ;
struct TYPE_26__ {int have_backrefs; int num_tags; int num_transitions; int num_states; int cflags; TYPE_2__* final; TYPE_2__* initial; int /*<<< orphan*/ * firstpos_chars; TYPE_2__* transitions; int /*<<< orphan*/ * submatch_data; int /*<<< orphan*/ * minimal_tags; TYPE_4__* tag_directions; scalar_t__ num_submatches; scalar_t__ have_approx; } ;
typedef  TYPE_3__ tre_tnfa_t ;
struct TYPE_27__ {char const* re; int cflags; int max_backref; int position; scalar_t__ submatch_id; TYPE_7__* n; int /*<<< orphan*/ * stack; int /*<<< orphan*/ * mem; } ;
typedef  TYPE_4__ tre_tag_direction_t ;
typedef  int /*<<< orphan*/  tre_submatch_data_t ;
typedef  int /*<<< orphan*/  tre_stack_t ;
struct TYPE_28__ {size_t position; scalar_t__* tags; int /*<<< orphan*/  assertions; } ;
typedef  TYPE_5__ tre_pos_and_tags_t ;
typedef  TYPE_4__ tre_parse_ctx_t ;
typedef  int /*<<< orphan*/ * tre_mem_t ;
struct TYPE_29__ {TYPE_1__* lastpos; TYPE_5__* firstpos; } ;
typedef  TYPE_7__ tre_ast_node_t ;
struct TYPE_30__ {void* TRE_REGEX_T_FIELD; scalar_t__ re_nsub; } ;
typedef  TYPE_8__ regex_t ;
typedef  scalar_t__ reg_errcode_t ;
typedef  int /*<<< orphan*/  parse_ctx ;
struct TYPE_24__ {size_t position; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_EXIT (int) ; 
 int REG_ESPACE ; 
 int REG_ESUBREG ; 
 int REG_NOSUB ; 
 scalar_t__ REG_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  regfree (TYPE_8__*) ; 
 scalar_t__ tre_add_tags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*,TYPE_3__*) ; 
 TYPE_7__* tre_ast_new_catenation (int /*<<< orphan*/ *,TYPE_7__*,TYPE_7__*) ; 
 TYPE_7__* tre_ast_new_literal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tre_ast_to_tnfa (TYPE_7__*,TYPE_2__*,int*,int*) ; 
 scalar_t__ tre_compute_nfl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*) ; 
 scalar_t__ tre_expand_ast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*,int*,TYPE_4__*) ; 
 int /*<<< orphan*/  tre_mem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tre_mem_new () ; 
 scalar_t__ tre_parse (TYPE_4__*) ; 
 int /*<<< orphan*/  tre_stack_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tre_stack_new (int,int,int) ; 
 void* xcalloc (unsigned int,int) ; 
 int /*<<< orphan*/  xfree (int*) ; 
 void* xmalloc (int) ; 

int
regcomp(regex_t *restrict preg, const char *restrict regex, int cflags)
{
  tre_stack_t *stack;
  tre_ast_node_t *tree, *tmp_ast_l, *tmp_ast_r;
  tre_pos_and_tags_t *p;
  int *counts = NULL, *offs = NULL;
  int i, add = 0;
  tre_tnfa_transition_t *transitions, *initial;
  tre_tnfa_t *tnfa = NULL;
  tre_submatch_data_t *submatch_data;
  tre_tag_direction_t *tag_directions = NULL;
  reg_errcode_t errcode;
  tre_mem_t mem;

  /* Parse context. */
  tre_parse_ctx_t parse_ctx;

  /* Allocate a stack used throughout the compilation process for various
     purposes. */
  stack = tre_stack_new(512, 1024000, 128);
  if (!stack)
    return REG_ESPACE;
  /* Allocate a fast memory allocator. */
  mem = tre_mem_new();
  if (!mem)
    {
      tre_stack_destroy(stack);
      return REG_ESPACE;
    }

  /* Parse the regexp. */
  memset(&parse_ctx, 0, sizeof(parse_ctx));
  parse_ctx.mem = mem;
  parse_ctx.stack = stack;
  parse_ctx.re = regex;
  parse_ctx.cflags = cflags;
  parse_ctx.max_backref = -1;
  errcode = tre_parse(&parse_ctx);
  if (errcode != REG_OK)
    ERROR_EXIT(errcode);
  preg->re_nsub = parse_ctx.submatch_id - 1;
  tree = parse_ctx.n;

#ifdef TRE_DEBUG
  tre_ast_print(tree);
#endif /* TRE_DEBUG */

  /* Referring to nonexistent subexpressions is illegal. */
  if (parse_ctx.max_backref > (int)preg->re_nsub)
    ERROR_EXIT(REG_ESUBREG);

  /* Allocate the TNFA struct. */
  tnfa = xcalloc(1, sizeof(tre_tnfa_t));
  if (tnfa == NULL)
    ERROR_EXIT(REG_ESPACE);
  tnfa->have_backrefs = parse_ctx.max_backref >= 0;
  tnfa->have_approx = 0;
  tnfa->num_submatches = parse_ctx.submatch_id;

  /* Set up tags for submatch addressing.  If REG_NOSUB is set and the
     regexp does not have back references, this can be skipped. */
  if (tnfa->have_backrefs || !(cflags & REG_NOSUB))
    {

      /* Figure out how many tags we will need. */
      errcode = tre_add_tags(NULL, stack, tree, tnfa);
      if (errcode != REG_OK)
	ERROR_EXIT(errcode);

      if (tnfa->num_tags > 0)
	{
	  tag_directions = xmalloc(sizeof(*tag_directions)
				   * (tnfa->num_tags + 1));
	  if (tag_directions == NULL)
	    ERROR_EXIT(REG_ESPACE);
	  tnfa->tag_directions = tag_directions;
	  memset(tag_directions, -1,
		 sizeof(*tag_directions) * (tnfa->num_tags + 1));
	}
      tnfa->minimal_tags = xcalloc((unsigned)tnfa->num_tags * 2 + 1,
				   sizeof(*tnfa->minimal_tags));
      if (tnfa->minimal_tags == NULL)
	ERROR_EXIT(REG_ESPACE);

      submatch_data = xcalloc((unsigned)parse_ctx.submatch_id,
			      sizeof(*submatch_data));
      if (submatch_data == NULL)
	ERROR_EXIT(REG_ESPACE);
      tnfa->submatch_data = submatch_data;

      errcode = tre_add_tags(mem, stack, tree, tnfa);
      if (errcode != REG_OK)
	ERROR_EXIT(errcode);

    }

  /* Expand iteration nodes. */
  errcode = tre_expand_ast(mem, stack, tree, &parse_ctx.position,
			   tag_directions);
  if (errcode != REG_OK)
    ERROR_EXIT(errcode);

  /* Add a dummy node for the final state.
     XXX - For certain patterns this dummy node can be optimized away,
	   for example "a*" or "ab*".	Figure out a simple way to detect
	   this possibility. */
  tmp_ast_l = tree;
  tmp_ast_r = tre_ast_new_literal(mem, 0, 0, parse_ctx.position++);
  if (tmp_ast_r == NULL)
    ERROR_EXIT(REG_ESPACE);

  tree = tre_ast_new_catenation(mem, tmp_ast_l, tmp_ast_r);
  if (tree == NULL)
    ERROR_EXIT(REG_ESPACE);

  errcode = tre_compute_nfl(mem, stack, tree);
  if (errcode != REG_OK)
    ERROR_EXIT(errcode);

  counts = xmalloc(sizeof(int) * parse_ctx.position);
  if (counts == NULL)
    ERROR_EXIT(REG_ESPACE);

  offs = xmalloc(sizeof(int) * parse_ctx.position);
  if (offs == NULL)
    ERROR_EXIT(REG_ESPACE);

  for (i = 0; i < parse_ctx.position; i++)
    counts[i] = 0;
  tre_ast_to_tnfa(tree, NULL, counts, NULL);

  add = 0;
  for (i = 0; i < parse_ctx.position; i++)
    {
      offs[i] = add;
      add += counts[i] + 1;
      counts[i] = 0;
    }
  transitions = xcalloc((unsigned)add + 1, sizeof(*transitions));
  if (transitions == NULL)
    ERROR_EXIT(REG_ESPACE);
  tnfa->transitions = transitions;
  tnfa->num_transitions = add;

  errcode = tre_ast_to_tnfa(tree, transitions, counts, offs);
  if (errcode != REG_OK)
    ERROR_EXIT(errcode);

  tnfa->firstpos_chars = NULL;

  p = tree->firstpos;
  i = 0;
  while (p->position >= 0)
    {
      i++;
      p++;
    }

  initial = xcalloc((unsigned)i + 1, sizeof(tre_tnfa_transition_t));
  if (initial == NULL)
    ERROR_EXIT(REG_ESPACE);
  tnfa->initial = initial;

  i = 0;
  for (p = tree->firstpos; p->position >= 0; p++)
    {
      initial[i].state = transitions + offs[p->position];
      initial[i].state_id = p->position;
      initial[i].tags = NULL;
      /* Copy the arrays p->tags, and p->params, they are allocated
	 from a tre_mem object. */
      if (p->tags)
	{
	  int j;
	  for (j = 0; p->tags[j] >= 0; j++);
	  initial[i].tags = xmalloc(sizeof(*p->tags) * (j + 1));
	  if (!initial[i].tags)
	    ERROR_EXIT(REG_ESPACE);
	  memcpy(initial[i].tags, p->tags, sizeof(*p->tags) * (j + 1));
	}
      initial[i].assertions = p->assertions;
      i++;
    }
  initial[i].state = NULL;

  tnfa->num_transitions = add;
  tnfa->final = transitions + offs[tree->lastpos[0].position];
  tnfa->num_states = parse_ctx.position;
  tnfa->cflags = cflags;

  tre_mem_destroy(mem);
  tre_stack_destroy(stack);
  xfree(counts);
  xfree(offs);

  preg->TRE_REGEX_T_FIELD = (void *)tnfa;
  return REG_OK;

 error_exit:
  /* Free everything that was allocated and return the error code. */
  tre_mem_destroy(mem);
  if (stack != NULL)
    tre_stack_destroy(stack);
  if (counts != NULL)
    xfree(counts);
  if (offs != NULL)
    xfree(offs);
  preg->TRE_REGEX_T_FIELD = (void *)tnfa;
  regfree(preg);
  return errcode;
}