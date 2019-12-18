#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int len; char* str; } ;
typedef  TYPE_1__ string_ty ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,char*) ; 

__attribute__((used)) static void do_string(string_ty x) {
	printf("%d,<code>'%s'</code>", x.len, x.str);
}