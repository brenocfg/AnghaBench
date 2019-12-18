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
typedef  int* uuid_t ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  scratch ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int SK_FEATURE_NETNS ; 
 int /*<<< orphan*/  SYSPROTO_CONTROL ; 
 int /*<<< orphan*/  T_EXPECT_EQ (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_EQ_ULONG (unsigned long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_FALSE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_POSIX_FAILURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_POSIX_ZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_TRUE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 int /*<<< orphan*/  g_OPT_ENABLE_CHANNEL ; 
 int /*<<< orphan*/  g_OPT_ENABLE_FLOWSWITCH ; 
 int /*<<< orphan*/  g_OPT_ENABLE_NETIF ; 
 int /*<<< orphan*/  g_OPT_GET_CHANNEL_UUID ; 
 scalar_t__ g_is_ipsec_test ; 
 int get_skywalk_features () ; 
 int /*<<< orphan*/  getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  uuid_clear (int*) ; 
 int /*<<< orphan*/  uuid_is_null (int*) ; 

__attribute__((used)) static void
check_enables(int tunsock, int enable_netif, int enable_flowswitch, int enable_channel, uuid_t uuid)
{
	int scratch;
	socklen_t scratchlen, uuidlen;
	uuid_t scratchuuid;
	if (!uuid) {
		uuid = scratchuuid;
	}

	//T_LOG("checking tunsock %d", tunsock);

	scratchlen = sizeof(scratch);
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(getsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_NETIF,
			&scratch, &scratchlen), NULL);
	T_QUIET; T_EXPECT_EQ_ULONG((unsigned long )scratchlen, sizeof(scratch), NULL);
	T_QUIET; T_EXPECT_EQ(scratch, enable_netif, NULL);

	scratchlen = sizeof(scratch);
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(getsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_FLOWSWITCH,
			&scratch, &scratchlen), NULL);
	T_QUIET; T_EXPECT_EQ_ULONG((unsigned long )scratchlen, sizeof(scratch), NULL);
	if (get_skywalk_features() & SK_FEATURE_NETNS) {
		if (enable_netif) {
			T_QUIET; T_EXPECT_EQ(scratch, enable_flowswitch, NULL);
		} else {
			T_QUIET; T_EXPECT_EQ(scratch, 0, NULL);
		}
	} else {
		T_QUIET; T_EXPECT_EQ(scratch, 0, NULL);
	}

	scratchlen = sizeof(scratch);
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(getsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_CHANNEL,
			&scratch, &scratchlen), NULL);
	T_QUIET; T_EXPECT_EQ_ULONG((unsigned long )scratchlen, sizeof(scratch), NULL);
	if (g_is_ipsec_test && !enable_netif) {
		T_QUIET; T_EXPECT_EQ(scratch, 0, NULL);
	} else {
		T_QUIET; T_EXPECT_EQ(scratch, enable_channel, NULL);
	}

	if (scratch) {
		uuid_clear(uuid);
		uuidlen = sizeof(uuid_t);
		T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(getsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_GET_CHANNEL_UUID,
				uuid, &uuidlen), NULL);
		T_QUIET; T_EXPECT_EQ_ULONG((unsigned long )uuidlen, sizeof(uuid_t), NULL);
		T_QUIET; T_EXPECT_FALSE(uuid_is_null(uuid), NULL);
	} else {
		uuid_clear(uuid);
		uuidlen = sizeof(uuid_t);
		T_QUIET; T_EXPECT_POSIX_FAILURE(getsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_GET_CHANNEL_UUID,
				uuid, &uuidlen), ENXIO, NULL);
		T_QUIET; T_EXPECT_EQ_ULONG((unsigned long )uuidlen, sizeof(uuid_t), NULL);
		T_QUIET; T_EXPECT_TRUE(uuid_is_null(uuid), NULL);
	}
}