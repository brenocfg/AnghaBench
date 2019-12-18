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
typedef  int /*<<< orphan*/  FEATURES_T ;

/* Variables and functions */
 int /*<<< orphan*/  FEATURES_UNPACK_ALPHA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FEATURES_UNPACK_MULTI (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bindable_rgb(FEATURES_T features)
{
   return !FEATURES_UNPACK_MULTI(features) && !FEATURES_UNPACK_ALPHA(features);
}