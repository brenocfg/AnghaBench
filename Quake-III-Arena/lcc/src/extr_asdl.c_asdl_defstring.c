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

/* Variables and functions */
 int /*<<< orphan*/  Text_box (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcc_Defstring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stringn (char*,int) ; 

__attribute__((used)) static void asdl_defstring(int len, char *str) {
	put(rcc_Defstring(Text_box(stringn(str, len), len)));
}