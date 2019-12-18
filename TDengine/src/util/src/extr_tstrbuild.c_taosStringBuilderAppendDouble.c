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
typedef  int /*<<< orphan*/  SStringBuilder ;

/* Variables and functions */
 size_t sprintf (char*,char*,double) ; 
 int /*<<< orphan*/  taosStringBuilderAppendStringLen (int /*<<< orphan*/ *,char*,size_t) ; 

void taosStringBuilderAppendDouble(SStringBuilder* sb, double v) {
  char   buf[64];
  size_t len = sprintf(buf, "%.9lf", v);
  taosStringBuilderAppendStringLen(sb, buf, len);
}