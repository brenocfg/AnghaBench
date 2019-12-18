#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  name; scalar_t__ flags; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ Var ;
struct TYPE_11__ {int flags; char* name; int /*<<< orphan*/  context; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ Hash_Entry ;
typedef  TYPE_3__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_AddBytes (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  Buf_Init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 TYPE_2__* Hash_CreateEntry (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Hash_SetValue (TYPE_2__*,TYPE_1__*) ; 
 int INTERNAL ; 
 int /*<<< orphan*/  VAR ; 
 TYPE_1__* bmake_malloc (int) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
VarAdd(const char *name, const char *val, GNode *ctxt)
{
    Var   	  *v;
    int		  len;
    Hash_Entry    *h;

    v = bmake_malloc(sizeof(Var));

    len = val ? strlen(val) : 0;
    Buf_Init(&v->val, len+1);
    Buf_AddBytes(&v->val, len, val);

    v->flags = 0;

    h = Hash_CreateEntry(&ctxt->context, name, NULL);
    Hash_SetValue(h, v);
    v->name = h->name;
    if (DEBUG(VAR) && (ctxt->flags & INTERNAL) == 0) {
	fprintf(debug_file, "%s:%s = %s\n", ctxt->name, name, val);
    }
}