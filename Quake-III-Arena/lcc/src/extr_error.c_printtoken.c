#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int size; } ;
struct TYPE_12__ {char* p; } ;
struct TYPE_8__ {TYPE_5__ v; } ;
struct TYPE_9__ {TYPE_1__ c; } ;
struct TYPE_13__ {TYPE_4__* type; TYPE_2__ u; } ;
struct TYPE_11__ {int size; TYPE_7__* type; } ;
struct TYPE_10__ {int size; } ;

/* Variables and functions */
#define  FCON 131 
#define  ICON 130 
#define  ID 129 
#define  SCON 128 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cp ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ischar (TYPE_7__*) ; 
 int /*<<< orphan*/  stderr ; 
 int t ; 
 int token ; 
 TYPE_6__* tsym ; 
 int vtoa (TYPE_4__*,TYPE_5__) ; 
 TYPE_3__* widechar ; 

__attribute__((used)) static void printtoken(void) {
	switch (t) {
	case ID: fprint(stderr, " `%s'", token); break;
	case ICON:
		fprint(stderr, " `%s'", vtoa(tsym->type, tsym->u.c.v));
		break;
	case SCON: {
		int i, n;
		if (ischar(tsym->type->type)) {
			char *s = tsym->u.c.v.p;
			n = tsym->type->size;
			fprint(stderr, " \"");
			for (i = 0; i < 20 && i < n && *s; s++, i++)
				if (*s < ' ' || *s >= 0177)
					fprint(stderr, "\\%o", *s);
				else
					fprint(stderr, "%c", *s);
		} else {	/* wchar_t string */
			unsigned int *s = tsym->u.c.v.p;
			assert(tsym->type->type->size == widechar->size);
			n = tsym->type->size/widechar->size;
			fprint(stderr, " L\"");
			for (i = 0; i < 20 && i < n && *s; s++, i++)
				if (*s < ' ' || *s >= 0177)
					fprint(stderr, "\\x%x", *s);
				else
					fprint(stderr, "%c", *s);
		}
		if (i < n)
			fprint(stderr, " ...");
		else
			fprint(stderr, "\"");
		break;
		}
	case FCON:
		fprint(stderr, " `%S'", token, (char*)cp - token);
		break;
	case '`': case '\'': fprint(stderr, " \"%k\"", t); break;
	default: fprint(stderr, " `%k'", t);
	}
}