#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {scalar_t__ OsType; } ;
struct TYPE_8__ {int Bridge; scalar_t__ Beta; } ;
struct TYPE_7__ {scalar_t__ ServerType; int IsInVm; TYPE_3__* Cedar; int /*<<< orphan*/ * DDnsClient; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  CAPSLIST ;

/* Variables and functions */
 int /*<<< orphan*/  AddCapsBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  AddCapsInt (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ EthIsInterfaceDescriptionSupportedUnix () ; 
 int GET_KETA (int /*<<< orphan*/ ,int) ; 
 TYPE_6__* GetOsInfo () ; 
 int /*<<< orphan*/  GetOsType () ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/  InitCapsList (int /*<<< orphan*/ *) ; 
 int IsAesNiSupported () ; 
 int IsBridgeSupported () ; 
 int IsEthSupported () ; 
 scalar_t__ IsNt () ; 
 scalar_t__ MAX_ACCESSLISTS ; 
 scalar_t__ MAX_GROUPS ; 
 scalar_t__ MAX_IP_TABLES ; 
 scalar_t__ MAX_MAC_TABLES ; 
 scalar_t__ MAX_NUM_L3_IF ; 
 scalar_t__ MAX_NUM_L3_SWITCH ; 
 scalar_t__ MAX_NUM_L3_TABLE ; 
 scalar_t__ MAX_PACKET_SIZE ; 
 scalar_t__ MAX_USERS ; 
 scalar_t__ NAT_MAX_SESSIONS ; 
 scalar_t__ const OSTYPE_BSD ; 
 scalar_t__ const OSTYPE_LINUX ; 
 scalar_t__ OSTYPE_WINDOWS_2000_PROFESSIONAL ; 
 scalar_t__ OS_IS_WINDOWS (scalar_t__) ; 
 scalar_t__ OS_IS_WINDOWS_NT (int /*<<< orphan*/ ) ; 
 scalar_t__ SERVER_MAX_SESSIONS_FOR_CARRIER_EDITION ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int SiIsAzureSupported (TYPE_1__*) ; 
 int SiIsEnterpriseFunctionsRestrictedOnOpenSource (TYPE_3__*) ; 
 int /*<<< orphan*/  UpdateGlobalServerFlags (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int Win32IsUsingSeLow () ; 

void GetServerCapsMain(SERVER *s, CAPSLIST *t)
{
	bool is_restricted = false;

	// Validate arguments
	if (s == NULL || t == NULL)
	{
		return;
	}

	is_restricted = SiIsEnterpriseFunctionsRestrictedOnOpenSource(s->Cedar);

	// Initialize
	InitCapsList(t);

	// Maximum Ethernet packet size
	AddCapsInt(t, "i_max_packet_size", MAX_PACKET_SIZE);

	if (s->Cedar->Bridge == false)
	{
		UINT max_sessions, max_clients, max_bridges, max_user_creations;

		max_clients = INFINITE;
		max_bridges = INFINITE;
		max_sessions = SERVER_MAX_SESSIONS_FOR_CARRIER_EDITION;
		max_user_creations = INFINITE;

		// Maximum number of virtual HUBs
		AddCapsInt(t, "i_max_hubs", SERVER_MAX_SESSIONS_FOR_CARRIER_EDITION);

		// The maximum number of concurrent sessions
		AddCapsInt(t, "i_max_sessions", max_sessions);

		// Maximum number of creatable users
		AddCapsInt(t, "i_max_user_creation", max_user_creations);

		// Maximum number of clients
		AddCapsInt(t, "i_max_clients", max_clients);

		// Maximum number of bridges
		AddCapsInt(t, "i_max_bridges", max_bridges);

		if (s->ServerType != SERVER_TYPE_FARM_MEMBER)
		{
			// Maximum number of registrable users / Virtual HUB
			AddCapsInt(t, "i_max_users_per_hub", MAX_USERS);

			// Maximum number of registrable groups / Virtual HUB
			AddCapsInt(t, "i_max_groups_per_hub", MAX_GROUPS);

			// Maximum number of registrable access list entries / Virtual HUB
			AddCapsInt(t, "i_max_access_lists", MAX_ACCESSLISTS);
		}
		else
		{
			// Maximum number of registrable users / Virtual HUB
			AddCapsInt(t, "i_max_users_per_hub", 0);

			// Maximum number of registrable groups / Virtual HUB
			AddCapsInt(t, "i_max_groups_per_hub", 0);

			// Maximum number of registrable access list entries / Virtual HUB
			AddCapsInt(t, "i_max_access_lists", 0);
		}

		// The policy related to multiple logins
		AddCapsBool(t, "b_support_limit_multilogin", true);

		// QoS / VoIP
		AddCapsBool(t, "b_support_qos", true);

		// syslog
		AddCapsBool(t, "b_support_syslog", true);

		// IPsec
		// (Only works in stand-alone mode currently)
		AddCapsBool(t, "b_support_ipsec", (s->ServerType == SERVER_TYPE_STANDALONE));

		// SSTP
		// (Only works in stand-alone mode currently)
		AddCapsBool(t, "b_support_sstp", (s->ServerType == SERVER_TYPE_STANDALONE));

		// OpenVPN
		// (Only works in stand-alone mode currently)
		AddCapsBool(t, "b_support_openvpn", (s->ServerType == SERVER_TYPE_STANDALONE));

		// DDNS
		AddCapsBool(t, "b_support_ddns", (s->DDnsClient != NULL));

		if (s->DDnsClient != NULL)
		{
			// DDNS via Proxy
			AddCapsBool(t, "b_support_ddns_proxy", true);
		}

		// VPN over ICMP, VPN over DNS
		AddCapsBool(t, "b_support_special_listener", true);
	}
	else
	{
		// Maximum number of virtual HUBs
		AddCapsInt(t, "i_max_hubs", 0);

		// The maximum number of concurrent sessions
		AddCapsInt(t, "i_max_sessions", 0);

		// Maximum number of clients
		AddCapsInt(t, "i_max_clients", 0);

		// Maximum number of bridges
		AddCapsInt(t, "i_max_bridges", 0);

		// Maximum number of registrable users / Virtual HUB
		AddCapsInt(t, "i_max_users_per_hub", 0);

		// Maximum number of registrable groups / Virtual HUB
		AddCapsInt(t, "i_max_groups_per_hub", 0);

		// Maximum number of registrable access list entries / Virtual HUB
		AddCapsInt(t, "i_max_access_lists", 0);

		// QoS / VoIP
		AddCapsBool(t, "b_support_qos", true);

		// syslog
		AddCapsBool(t, "b_support_syslog", true);

		// IPsec
		AddCapsBool(t, "b_support_ipsec", false);

		// SSTP
		AddCapsBool(t, "b_support_sstp", false);

		// OpenVPN
		AddCapsBool(t, "b_support_openvpn", false);

		// DDNS
		AddCapsBool(t, "b_support_ddns", false);

		// VPN over ICMP, VPN over DNS
		AddCapsBool(t, "b_support_special_listener", false);
	}

	// Changing the type of Virtual HUB in cluster is prohibited
	AddCapsBool(t, "b_cluster_hub_type_fixed", true);

	// Maximum MAC address table  size / Virtual HUB
	AddCapsInt(t, "i_max_mac_tables", MAX_MAC_TABLES);

	// Maximum IP address table  size / Virtual HUB
	AddCapsInt(t, "i_max_ip_tables", MAX_IP_TABLES);

	// SecureNAT function is available
	AddCapsBool(t, "b_support_securenat", true);

	// Pushing routing table function of SecureNAT Virtual DHCP Server is available
	AddCapsBool(t, "b_suppport_push_route", !is_restricted);
	AddCapsBool(t, "b_suppport_push_route_config", true);

	if (s->ServerType != SERVER_TYPE_STANDALONE)
	{
		AddCapsBool(t, "b_virtual_nat_disabled", true);
	}

	// Maximum NAT table size / Virtual HUB
	AddCapsInt(t, "i_max_secnat_tables", NAT_MAX_SESSIONS);

	// Cascade connection
	if (s->ServerType == SERVER_TYPE_STANDALONE)
	{
		AddCapsBool(t, "b_support_cascade", true);
	}
	else
	{
		AddCapsBool(t, "b_support_cascade", false);
	}

	if (s->Cedar->Bridge)
	{
		// Bridge mode
		AddCapsBool(t, "b_bridge", true);
	}
	else if (s->ServerType == SERVER_TYPE_STANDALONE)
	{
		// Stand-alone mode
		AddCapsBool(t, "b_standalone", true);
	}
	else if (s->ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		// Cluster controller mode
		AddCapsBool(t, "b_cluster_controller", true);
	}
	else
	{
		// Cluster member mode
		AddCapsBool(t, "b_cluster_member", true);
	}

	// Virtual HUB is modifiable
	AddCapsBool(t, "b_support_config_hub", s->ServerType != SERVER_TYPE_FARM_MEMBER &&
		s->Cedar->Bridge == false);

	// VPN client can be connected
	AddCapsBool(t, "b_vpn_client_connect", s->Cedar->Bridge == false ? true : false);

	// External authentication server is available
	AddCapsBool(t, "b_support_radius", s->ServerType != SERVER_TYPE_FARM_MEMBER &&
		s->Cedar->Bridge == false);

	// Local-bridge function is available
	AddCapsBool(t, "b_local_bridge", IsBridgeSupported());

	if (OS_IS_WINDOWS(GetOsInfo()->OsType))
	{
		// Packet capture driver is not installed
		AddCapsBool(t, "b_must_install_pcap", IsEthSupported() == false ? true : false);
	}
	else
	{
		// Regard that the driver is installed in the Linux version
		AddCapsBool(t, "b_must_install_pcap", false);
	}

	if (IsBridgeSupported())
	{
		// TUN / TAP device availability (Linux and BSD)
		const UINT OsType = GetOsInfo()->OsType;
		AddCapsBool(t, "b_tap_supported", OsType == OSTYPE_LINUX || OsType == OSTYPE_BSD);
	}

	// Cascade connection
	if (s->ServerType == SERVER_TYPE_STANDALONE)
	{
		AddCapsBool(t, "b_support_cascade", true);
	}
	else
	{
		AddCapsBool(t, "b_support_cascade", false);
	}

	// Server authentication can be used in cascade connection
	AddCapsBool(t, "b_support_cascade_cert", true);

	//  the log file settings is modifiable
	AddCapsBool(t, "b_support_config_log", s->ServerType != SERVER_TYPE_FARM_MEMBER);

	// Automatic deletion of log file is available
	AddCapsBool(t, "b_support_autodelete", true);

	// Config file operation is available
	AddCapsBool(t, "b_support_config_rw", true);

	// Attribute of each Virtual HUB can be set
	AddCapsBool(t, "b_support_hub_admin_option", true);

	// Client certificate can be set in a cascade connection
	AddCapsBool(t, "b_support_cascade_client_cert", true);

	// Virtual HUB can be hidden
	AddCapsBool(t, "b_support_hide_hub", true);

	// Integrated management
	AddCapsBool(t, "b_support_cluster_admin", true);

	// Flag of open-source version
	AddCapsBool(t, "b_is_softether", true);

	if (s->Cedar->Bridge == false)
	{

		// The virtual layer 3 switch function is available
		AddCapsBool(t, "b_support_layer3", true);

		AddCapsInt(t, "i_max_l3_sw", MAX_NUM_L3_SWITCH);
		AddCapsInt(t, "i_max_l3_if", MAX_NUM_L3_IF);
		AddCapsInt(t, "i_max_l3_table", MAX_NUM_L3_TABLE);

		// Can act as a part of a cluster
		AddCapsBool(t, "b_support_cluster", true);
	}
	else
	{
		AddCapsBool(t, "b_support_layer3", false);

		AddCapsInt(t, "i_max_l3_sw", 0);
		AddCapsInt(t, "i_max_l3_if", 0);
		AddCapsInt(t, "i_max_l3_table", 0);

		AddCapsBool(t, "b_support_cluster", false);
	}

	if (s->ServerType != SERVER_TYPE_FARM_MEMBER && s->Cedar->Bridge == false)
	{
		// Support for CRL
		AddCapsBool(t, "b_support_crl", true);

		// Supports AC
		AddCapsBool(t, "b_support_ac", true);
	}

	// Supports downloading a log file
	AddCapsBool(t, "b_support_read_log", true);

	// Cascade connection can be renamed
	AddCapsBool(t, "b_support_rename_cascade", true);


	if (s->Cedar->Beta)
	{
		// Beta version
		AddCapsBool(t, "b_beta_version", true);
	}

	// VM discrimination
	AddCapsBool(t, "b_is_in_vm", s->IsInVm);

	// Support for display name of the network connection for the local bridge
#ifdef	OS_WIN32
	if (IsBridgeSupported() && IsNt() && GetOsInfo()->OsType >= OSTYPE_WINDOWS_2000_PROFESSIONAL)
	{
		AddCapsBool(t, "b_support_network_connection_name", true);
	}
#else	// OS_WIN32
	if (IsBridgeSupported() && EthIsInterfaceDescriptionSupportedUnix())
	{
		AddCapsBool(t, "b_support_network_connection_name", true);
	}
#endif	// OS_WIN32

	// Support for MAC address filtering
	AddCapsBool(t, "b_support_check_mac", true);

	// Support for status check of the TCP connection
	AddCapsBool(t, "b_support_check_tcp_state", true);

	// Can specify multiple server and retry intervals in Radius authentication
	AddCapsBool(t, "b_support_radius_retry_interval_and_several_servers", s->ServerType != SERVER_TYPE_FARM_MEMBER &&
		s->Cedar->Bridge == false);

	// Can manage the ID of the tagged VLAN in the MAC address table
	AddCapsBool(t, "b_support_vlan", true);

	// Support for Virtual HUB extended options
	if ((s->Cedar->Bridge == false) &&
		(s->ServerType == SERVER_TYPE_STANDALONE || s->ServerType == SERVER_TYPE_FARM_CONTROLLER))
	{
		AddCapsBool(t, "b_support_hub_ext_options", true);
	}
	else
	{
		AddCapsBool(t, "b_support_hub_ext_options", false);
	}

	// Support for Security Policy version 3.0
	AddCapsBool(t, "b_support_policy_ver_3", true);

	// Support for IPv6 access list
	AddCapsBool(t, "b_support_ipv6_acl", true);

	// Support for setting of delay, jitter and packet loss in the access list
	AddCapsBool(t, "b_support_ex_acl", true);

	// Support for URL redirection in the access list
	AddCapsBool(t, "b_support_redirect_url_acl", true);

	// Supports the specification by the group name in the access list
	AddCapsBool(t, "b_support_acl_group", true);

	// Support for IPv6 in connection source IP restriction list
	AddCapsBool(t, "b_support_ipv6_ac", true);

	// Support for VLAN tagged packet transmission configuration tool
	AddCapsBool(t, "b_support_eth_vlan", (OS_IS_WINDOWS_NT(GetOsType()) && GET_KETA(GetOsType(), 100) >= 2));

	// Support for the message display function when the VPN connect to the Virtual HUB
	AddCapsBool(t, "b_support_msg", true);

	// UDP acceleration feature
	AddCapsBool(t, "b_support_udp_acceleration", true);

	// AES acceleration function
	AddCapsBool(t, "b_support_aes_ni", IsAesNiSupported());

#ifdef	OS_WIN32
	// SeLow driver
	AddCapsBool(t, "b_using_selow_driver", Win32IsUsingSeLow());
#endif	// OS_WIN32

	// VPN Azure function
	AddCapsBool(t, "b_support_azure", SiIsAzureSupported(s));

	// VPN3
	AddCapsBool(t, "b_vpn3", true);

	// VPN4
	AddCapsBool(t, "b_vpn4", true);


	UpdateGlobalServerFlags(s, t);
}