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
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 char* buf_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_buffer () ; 
 int /*<<< orphan*/  print (int /*<<< orphan*/ *,char) ; 

char *quote_cstring_len(char *p, int len) {
    Buffer *b = make_buffer();
    for (int i = 0; i < len; i++)
        print(b, p[i]);
    return buf_body(b);
}