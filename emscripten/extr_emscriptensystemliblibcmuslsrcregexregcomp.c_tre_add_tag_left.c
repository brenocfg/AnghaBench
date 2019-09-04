#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tre_mem_t ;
struct TYPE_6__ {TYPE_1__* right; int /*<<< orphan*/ * left; } ;
typedef  TYPE_2__ tre_catenation_t ;
struct TYPE_7__ {int /*<<< orphan*/  type; TYPE_2__* obj; } ;
typedef  TYPE_3__ tre_ast_node_t ;
typedef  int /*<<< orphan*/  reg_errcode_t ;
struct TYPE_5__ {int nullable; int submatch_id; scalar_t__ num_submatches; scalar_t__ num_tags; int /*<<< orphan*/ * lastpos; int /*<<< orphan*/ * firstpos; int /*<<< orphan*/  type; TYPE_2__* obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  CATENATION ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  REG_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/ * tre_ast_new_literal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 void* tre_mem_alloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static reg_errcode_t
tre_add_tag_left(tre_mem_t mem, tre_ast_node_t *node, int tag_id)
{
  tre_catenation_t *c;

  c = tre_mem_alloc(mem, sizeof(*c));
  if (c == NULL)
    return REG_ESPACE;
  c->left = tre_ast_new_literal(mem, TAG, tag_id, -1);
  if (c->left == NULL)
    return REG_ESPACE;
  c->right = tre_mem_alloc(mem, sizeof(tre_ast_node_t));
  if (c->right == NULL)
    return REG_ESPACE;

  c->right->obj = node->obj;
  c->right->type = node->type;
  c->right->nullable = -1;
  c->right->submatch_id = -1;
  c->right->firstpos = NULL;
  c->right->lastpos = NULL;
  c->right->num_tags = 0;
  c->right->num_submatches = 0;
  node->obj = c;
  node->type = CATENATION;
  return REG_OK;
}