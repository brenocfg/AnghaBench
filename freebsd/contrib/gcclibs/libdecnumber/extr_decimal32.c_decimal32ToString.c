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
typedef  int /*<<< orphan*/  decimal32 ;
typedef  int /*<<< orphan*/  decNumber ;

/* Variables and functions */
 int /*<<< orphan*/  decNumberToString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  decimal32ToNumber (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

char *
decimal32ToString (const decimal32 * d32, char *string)
{
  decNumber dn;			/* work */
  decimal32ToNumber (d32, &dn);
  decNumberToString (&dn, string);
  return string;
}