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
typedef  int /*<<< orphan*/  decimal128 ;
typedef  int /*<<< orphan*/  decNumber ;

/* Variables and functions */
 int /*<<< orphan*/  decNumberToEngString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  decimal128ToNumber (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

char *
decimal128ToEngString (const decimal128 * d128, char *string)
{
  decNumber dn;			/* work */
  decimal128ToNumber (d128, &dn);
  decNumberToEngString (&dn, string);
  return string;
}