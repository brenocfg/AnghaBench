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
struct type {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  extract_signed_integer (void const*,int /*<<< orphan*/ ) ; 

CORE_ADDR
signed_pointer_to_address (struct type *type, const void *buf)
{
  return extract_signed_integer (buf, TYPE_LENGTH (type));
}