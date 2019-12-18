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
typedef  int /*<<< orphan*/  lambda_body_vector ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LBV_COEFFICIENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LBV_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_lambda_vector (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
print_lambda_body_vector (FILE * outfile, lambda_body_vector body)
{
  print_lambda_vector (outfile, LBV_COEFFICIENTS (body), LBV_SIZE (body));
}