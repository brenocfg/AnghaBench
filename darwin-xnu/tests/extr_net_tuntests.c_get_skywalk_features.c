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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  features ;

/* Variables and functions */
 int SK_FEATURE_SKYWALK ; 
 int /*<<< orphan*/  T_ASSERT_EQ (size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_ASSERT_TRUE (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_POSIX_ZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 int /*<<< orphan*/  sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
get_skywalk_features(void)
{
	uint64_t features = 0;
	size_t len = sizeof(features);
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(sysctlbyname("kern.skywalk.features", &features, &len, NULL, 0), NULL);
	T_QUIET; T_ASSERT_EQ(len, sizeof(features), NULL);
	T_QUIET; T_ASSERT_TRUE(features & SK_FEATURE_SKYWALK, NULL);
	return features;
}