#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_10__ {int /*<<< orphan*/  (* defstring ) (int,char*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  i; } ;
struct TYPE_6__ {TYPE_2__ v; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
struct TYPE_8__ {int size; } ;

/* Variables and functions */
 TYPE_5__* IR ; 
 char gettok () ; 
 TYPE_4__* initvalue (int /*<<< orphan*/ ) ; 
 TYPE_3__* inttype ; 
 int /*<<< orphan*/  stub1 (int,char*) ; 
 int /*<<< orphan*/  stub2 (int,char*) ; 
 char t ; 

__attribute__((used)) static int initchar(int len, Type ty) {
	int n = 0;
	char buf[16], *s = buf;

	do {
		*s++ = initvalue(ty)->u.v.i;
		if (++n%inttype->size == 0) {
			(*IR->defstring)(inttype->size, buf);
			s = buf;
		}
		if (len > 0 && n >= len || t != ',')
			break;
		t = gettok();
	} while (t != '}');
	if (s > buf)
		(*IR->defstring)(s - buf, buf);
	return n;
}