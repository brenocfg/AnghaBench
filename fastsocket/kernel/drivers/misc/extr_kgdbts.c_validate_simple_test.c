#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t idx; TYPE_1__* tst; } ;
struct TYPE_3__ {int (* put_handler ) (char*,char*) ;char* put; } ;

/* Variables and functions */
 int stub1 (char*,char*) ; 
 TYPE_2__ ts ; 

__attribute__((used)) static int validate_simple_test(char *put_str)
{
	char *chk_str;

	if (ts.tst[ts.idx].put_handler)
		return ts.tst[ts.idx].put_handler(put_str,
			ts.tst[ts.idx].put);

	chk_str = ts.tst[ts.idx].put;
	if (*put_str == '$')
		put_str++;

	while (*chk_str != '\0' && *put_str != '\0') {
		/* If someone does a * to match the rest of the string, allow
		 * it, or stop if the recieved string is complete.
		 */
		if (*put_str == '#' || *chk_str == '*')
			return 0;
		if (*put_str != *chk_str)
			return 1;

		chk_str++;
		put_str++;
	}
	if (*chk_str == '\0' && (*put_str == '\0' || *put_str == '#'))
		return 0;

	return 1;
}