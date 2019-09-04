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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */

long tutil_tvdiff(struct timeval newer, struct timeval older)
{
  return (long)(newer.tv_sec-older.tv_sec)*1000+
    (long)(newer.tv_usec-older.tv_usec)/1000;
}