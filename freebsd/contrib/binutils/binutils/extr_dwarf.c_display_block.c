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
 char* _ (char*) ; 
 scalar_t__ byte_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned long) ; 

__attribute__((used)) static unsigned char *
display_block (unsigned char *data, unsigned long length)
{
  printf (_(" %lu byte block: "), length);

  while (length --)
    printf ("%lx ", (unsigned long) byte_get (data++, 1));

  return data;
}