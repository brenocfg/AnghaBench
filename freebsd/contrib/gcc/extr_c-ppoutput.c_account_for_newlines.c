#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  src_line; } ;

/* Variables and functions */
 TYPE_1__ print ; 

__attribute__((used)) static void
account_for_newlines (const unsigned char *str, size_t len)
{
  while (len--)
    if (*str++ == '\n')
      print.src_line++;
}