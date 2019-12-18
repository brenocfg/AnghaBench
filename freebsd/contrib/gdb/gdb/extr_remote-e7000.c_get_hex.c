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
 int convert_hex_digit (int) ; 
 int readchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static int
get_hex (int *start)
{
  int value = convert_hex_digit (*start);
  int try;

  *start = readchar (timeout);
  while ((try = convert_hex_digit (*start)) >= 0)
    {
      value <<= 4;
      value += try;
      *start = readchar (timeout);
    }
  return value;
}