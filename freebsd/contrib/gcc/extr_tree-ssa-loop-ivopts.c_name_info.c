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
typedef  int /*<<< orphan*/  tree ;
struct version_info {int dummy; } ;
struct ivopts_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 struct version_info* ver_info (struct ivopts_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct version_info *
name_info (struct ivopts_data *data, tree name)
{
  return ver_info (data, SSA_NAME_VERSION (name));
}