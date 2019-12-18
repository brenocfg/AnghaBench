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
typedef  int /*<<< orphan*/  uuid_t ;
struct sockaddr_ctl {int sc_len; scalar_t__ sc_unit; int /*<<< orphan*/  ctl_id; int /*<<< orphan*/  sc_id; int /*<<< orphan*/  ss_sysaddr; int /*<<< orphan*/  sc_family; int /*<<< orphan*/  ctl_name; } ;
struct sockaddr {int dummy; } ;
struct ctl_info {int sc_len; scalar_t__ sc_unit; int /*<<< orphan*/  ctl_id; int /*<<< orphan*/  sc_id; int /*<<< orphan*/  ss_sysaddr; int /*<<< orphan*/  sc_family; int /*<<< orphan*/  ctl_name; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  kernctl_info ;
typedef  int /*<<< orphan*/  kernctl_addr ;
typedef  int /*<<< orphan*/  enable_netif ;
typedef  int /*<<< orphan*/  enable_flowswitch ;
typedef  int /*<<< orphan*/  enable_channel ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SYSTEM ; 
 int /*<<< orphan*/  AF_SYS_CONTROL ; 
 int /*<<< orphan*/  CTLIOCGINFO ; 
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  PF_SYSTEM ; 
 int SK_FEATURE_NETNS ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SYSPROTO_CONTROL ; 
 int /*<<< orphan*/  T_EXPECT_EQ_ULONG (unsigned long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_FALSE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_POSIX_FAILURE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_POSIX_SUCCESS (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_POSIX_ZERO (int,char*) ; 
 int /*<<< orphan*/  T_EXPECT_TRUE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  check_enables (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  g_CONTROL_NAME ; 
 int /*<<< orphan*/  g_OPT_ENABLE_CHANNEL ; 
 int /*<<< orphan*/  g_OPT_ENABLE_FLOWSWITCH ; 
 int /*<<< orphan*/  g_OPT_ENABLE_NETIF ; 
 int /*<<< orphan*/  g_OPT_GET_CHANNEL_UUID ; 
 scalar_t__ g_is_ipsec_test ; 
 int get_skywalk_features () ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct sockaddr_ctl*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_ctl*,int /*<<< orphan*/ ,int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uuid_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_is_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
create_tunsock(int enable_netif, int enable_flowswitch, int enable_channel)
{
	int tunsock;
	struct ctl_info kernctl_info;
	struct sockaddr_ctl kernctl_addr;
	uuid_t uuid;
	socklen_t uuidlen;

startover:

	T_QUIET; T_EXPECT_POSIX_SUCCESS(tunsock = socket(PF_SYSTEM, SOCK_DGRAM, SYSPROTO_CONTROL), NULL);

	memset(&kernctl_info, 0, sizeof(kernctl_info));
	strlcpy(kernctl_info.ctl_name, g_CONTROL_NAME, sizeof(kernctl_info.ctl_name));
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(ioctl(tunsock, CTLIOCGINFO, &kernctl_info), NULL);

	memset(&kernctl_addr, 0, sizeof(kernctl_addr));
	kernctl_addr.sc_len = sizeof(kernctl_addr);
	kernctl_addr.sc_family = AF_SYSTEM;
	kernctl_addr.ss_sysaddr = AF_SYS_CONTROL;
	kernctl_addr.sc_id = kernctl_info.ctl_id;
	kernctl_addr.sc_unit = 0;

	//T_LOG("enable_netif = %d, enable_flowswitch = %d, enable_channel = %d",
	//enable_netif, enable_channel, enable_flowswitch);

	T_QUIET; T_EXPECT_POSIX_FAILURE(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_NETIF,
			&enable_netif, sizeof(enable_netif)), EINVAL, NULL);
	T_QUIET; T_EXPECT_POSIX_FAILURE(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_FLOWSWITCH,
			&enable_flowswitch, sizeof(enable_flowswitch)), EINVAL, NULL);
	T_QUIET; T_EXPECT_POSIX_FAILURE(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_CHANNEL,
			&enable_channel, sizeof(enable_channel)), EINVAL, NULL);
	uuid_clear(uuid);
	uuidlen = sizeof(uuid_t);
	T_QUIET; T_EXPECT_POSIX_FAILURE(getsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_GET_CHANNEL_UUID,
			uuid, &uuidlen), EINVAL, NULL);
	T_QUIET; T_EXPECT_EQ_ULONG((unsigned long )uuidlen, sizeof(uuid_t), NULL);
	T_QUIET; T_EXPECT_TRUE(uuid_is_null(uuid), NULL);

	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(bind(tunsock, (struct sockaddr *)&kernctl_addr, sizeof(kernctl_addr)), NULL);

	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_NETIF,
				&enable_netif, sizeof(enable_netif)), NULL);
	T_QUIET; T_EXPECT_POSIX_FAILURE(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_FLOWSWITCH,
			&enable_flowswitch, sizeof(enable_flowswitch)), EINVAL, NULL);
	T_QUIET; T_EXPECT_POSIX_FAILURE(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_CHANNEL,
			&enable_channel, sizeof(enable_channel)), EINVAL, NULL);
	uuid_clear(uuid);
	uuidlen = sizeof(uuid_t);
	T_QUIET; T_EXPECT_POSIX_FAILURE(getsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_GET_CHANNEL_UUID,
			uuid, &uuidlen), ENXIO, NULL);
	T_QUIET; T_EXPECT_EQ_ULONG((unsigned long )uuidlen, sizeof(uuid_t), NULL);
	T_QUIET; T_EXPECT_TRUE(uuid_is_null(uuid), NULL);

	int error = connect(tunsock, (struct sockaddr *)&kernctl_addr, sizeof(kernctl_addr));
	if (error == -1 && errno == EBUSY) {
		/* XXX remove this retry nonsense when this is fixed:
		 * <rdar://problem/37340313> creating an interface without specifying specific interface name should not return EBUSY
		 */
		close(tunsock);
		T_LOG("connect got EBUSY, sleeping 1 second before retry");
		sleep(1);
		goto startover;
	}
	T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(error, "connect()");

	T_QUIET; T_EXPECT_POSIX_FAILURE(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_NETIF,
			&enable_netif, sizeof(enable_netif)), EINVAL, NULL);

	if (get_skywalk_features() & SK_FEATURE_NETNS) {
		if (enable_netif) {
			T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_FLOWSWITCH,
					&enable_flowswitch, sizeof(enable_flowswitch)), NULL);
		} else {
			T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_FAILURE(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_FLOWSWITCH,
					&enable_flowswitch, sizeof(enable_flowswitch)), ENOENT, NULL);
		}
	} else {
		T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_FAILURE(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_FLOWSWITCH,
				&enable_flowswitch, sizeof(enable_flowswitch)), ENOTSUP, NULL);
	}

	if (enable_channel) {
		if (g_is_ipsec_test && !enable_netif) {
			/* ipsec doesn't support channels without a netif */
			T_QUIET; T_EXPECT_POSIX_FAILURE(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_CHANNEL,
					&enable_channel, sizeof(enable_channel)), EOPNOTSUPP, NULL);
			uuid_clear(uuid);
			uuidlen = sizeof(uuid_t);
			T_QUIET; T_EXPECT_POSIX_FAILURE(getsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_GET_CHANNEL_UUID,
					uuid, &uuidlen), ENXIO, NULL);
			T_QUIET; T_EXPECT_EQ_ULONG((unsigned long )uuidlen, sizeof(uuid_t), NULL);
			T_QUIET; T_EXPECT_TRUE(uuid_is_null(uuid), NULL);
		} else {
			T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_CHANNEL,
					&enable_channel, sizeof(enable_channel)), NULL);
			uuid_clear(uuid);
			uuidlen = sizeof(uuid_t);
			T_QUIET; T_WITH_ERRNO; T_EXPECT_POSIX_ZERO(getsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_GET_CHANNEL_UUID,
					uuid, &uuidlen), NULL);
			T_QUIET; T_EXPECT_EQ_ULONG((unsigned long )uuidlen, sizeof(uuid_t), NULL);
			T_QUIET; T_EXPECT_FALSE(uuid_is_null(uuid), NULL);
		}
	} else {
		T_QUIET; T_EXPECT_POSIX_FAILURE(setsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_ENABLE_CHANNEL,
				&enable_channel, sizeof(enable_channel)), ENXIO, NULL);
		uuid_clear(uuid);
		uuidlen = sizeof(uuid_t);
		T_QUIET; T_EXPECT_POSIX_FAILURE(getsockopt(tunsock, SYSPROTO_CONTROL, g_OPT_GET_CHANNEL_UUID,
				uuid, &uuidlen), ENXIO, NULL);
		T_QUIET; T_EXPECT_EQ_ULONG((unsigned long )uuidlen, sizeof(uuid_t), NULL);
		T_QUIET; T_EXPECT_TRUE(uuid_is_null(uuid), NULL);
	}

	check_enables(tunsock, enable_netif, enable_flowswitch, enable_channel, uuid);

	//T_LOG("Returning tunsock %d", tunsock);

	return tunsock;
}