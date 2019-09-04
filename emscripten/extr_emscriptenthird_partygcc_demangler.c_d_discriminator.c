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
struct d_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 long d_number (struct d_info*) ; 
 char d_peek_char (struct d_info*) ; 

__attribute__((used)) static int
d_discriminator (struct d_info *di)
{
  long discrim;

  if (d_peek_char (di) != '_')
    return 1;
  d_advance (di, 1);
  discrim = d_number (di);
  if (discrim < 0)
    return 0;
  return 1;
}