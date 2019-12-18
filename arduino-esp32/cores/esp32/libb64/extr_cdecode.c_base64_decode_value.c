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
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int base64_decode_value_signed (int /*<<< orphan*/ ) ; 

int base64_decode_value(char value_in){
  return base64_decode_value_signed(*((int8_t *) &value_in));
}