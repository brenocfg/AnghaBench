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
struct df {int dummy; } ;
struct dataflow {int dummy; } ;

/* Variables and functions */
 struct dataflow* df_add_problem (struct df*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  problem_RU ; 

struct dataflow *
df_ru_add_problem (struct df *df, int flags)
{
  return df_add_problem (df, &problem_RU, flags);
}