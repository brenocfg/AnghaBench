#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ Tree ;
struct TYPE_5__ {char* name; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  appendstr (char*) ; 
 int /*<<< orphan*/  frameno ; 
 scalar_t__ freturn (int /*<<< orphan*/ ) ; 
 scalar_t__ idtree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracefinis (TYPE_1__*) ; 
 int /*<<< orphan*/  tracevalue (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ voidtype ; 

__attribute__((used)) static void tracereturn(Symbol printer, Symbol f, Tree e) {
	appendstr(f->name); appendstr("#");
	tracevalue(idtree(frameno), 0);
	appendstr(" returned");
	if (freturn(f->type) != voidtype && e) {
		appendstr(" ");
		tracevalue(e, 0);
	}
	appendstr("\n");
	tracefinis(printer);
}