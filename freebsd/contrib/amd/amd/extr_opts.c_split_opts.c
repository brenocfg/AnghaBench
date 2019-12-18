#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct opt {char* name; char** optp; scalar_t__ sel_p; } ;

/* Variables and functions */
 scalar_t__ FSTREQ (char*,char*) ; 
 int /*<<< orphan*/  XLOG_USER ; 
 char* opt (char**) ; 
 struct opt* opt_fields ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
split_opts(char *opts, char *mapkey)
{
  char *o = opts;
  char *f;

  /*
   * For each user-specified option
   */
  for (f = opt(&o); *f; f = opt(&o)) {
    struct opt *op;
    char *eq = strchr(f, '=');
    char *opt = NULL;

    if (!eq)
      continue;

    if (*(eq-1) == '!' ||
	eq[1] == '=' ||
	eq[1] == '!') {	/* != or == or =! */
      continue;			/* we don't care about selectors */
    }

    if (*(eq-1) == ':') {	/* := */
      *(eq-1) = '\0';
    } else {
      /* old style assignment */
      eq[0] = '\0';
    }
    opt = eq + 1;

    /*
     * For each recognized option
     */
    for (op = opt_fields; op->name; op++) {
      /*
       * Check whether they match
       */
      if (FSTREQ(op->name, f)) {
	if (op->sel_p) {
	  plog(XLOG_USER, "key %s: Can't assign to a selector (%s)",
	       mapkey, op->name);
	  return 0;
	}
	*op->optp = opt;	/* actual assignment into fs_static */
	break;			/* break out of for loop */
      }	/* end of "if (FSTREQ(op->name, f))" statement  */
    } /* end of "for (op = opt_fields..." statement  */

    if (!op->name)
      plog(XLOG_USER, "key %s: Unrecognized key/option \"%s\"", mapkey, f);
  }

  return 1;
}