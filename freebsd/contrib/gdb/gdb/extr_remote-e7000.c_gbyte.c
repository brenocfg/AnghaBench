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
 int convert_hex_digit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gch () ; 

__attribute__((used)) static unsigned int
gbyte (void)
{
  int high = convert_hex_digit (gch ());
  int low = convert_hex_digit (gch ());

  return (high << 4) + low;
}