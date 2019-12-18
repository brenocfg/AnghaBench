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
typedef  int /*<<< orphan*/  string ;

/* Variables and functions */
 int /*<<< orphan*/  INTBUF_SIZE ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  string_append (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
string_append_template_idx (string *s, int idx)
{
  char buf[INTBUF_SIZE + 1 /* 'T' */];
  sprintf(buf, "T%d", idx);
  string_append (s, buf);
}