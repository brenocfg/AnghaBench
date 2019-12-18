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
typedef  int UINT ;

/* Variables and functions */
#define  OSTYPE_BSD 168 
#define  OSTYPE_CYGWIN 167 
#define  OSTYPE_LINUX 166 
#define  OSTYPE_MACOS_X 165 
#define  OSTYPE_SOLARIS 164 
#define  OSTYPE_UNIX_UNKNOWN 163 
#define  OSTYPE_WINDOWS_10 162 
#define  OSTYPE_WINDOWS_11 161 
#define  OSTYPE_WINDOWS_2000_ADVANCED_SERVER 160 
#define  OSTYPE_WINDOWS_2000_BACKOFFICE 159 
#define  OSTYPE_WINDOWS_2000_DATACENTER_SERVER 158 
#define  OSTYPE_WINDOWS_2000_PROFESSIONAL 157 
#define  OSTYPE_WINDOWS_2000_SBS 156 
#define  OSTYPE_WINDOWS_2000_SERVER 155 
#define  OSTYPE_WINDOWS_2003_BACKOFFICE 154 
#define  OSTYPE_WINDOWS_2003_DATACENTER 153 
#define  OSTYPE_WINDOWS_2003_ENTERPRISE 152 
#define  OSTYPE_WINDOWS_2003_SBS 151 
#define  OSTYPE_WINDOWS_2003_STANDARD 150 
#define  OSTYPE_WINDOWS_2003_WEB 149 
#define  OSTYPE_WINDOWS_7 148 
#define  OSTYPE_WINDOWS_8 147 
#define  OSTYPE_WINDOWS_81 146 
#define  OSTYPE_WINDOWS_95 145 
#define  OSTYPE_WINDOWS_98 144 
#define  OSTYPE_WINDOWS_LONGHORN_PROFESSIONAL 143 
#define  OSTYPE_WINDOWS_LONGHORN_SERVER 142 
#define  OSTYPE_WINDOWS_ME 141 
#define  OSTYPE_WINDOWS_NT_4_BACKOFFICE 140 
#define  OSTYPE_WINDOWS_NT_4_SERVER 139 
#define  OSTYPE_WINDOWS_NT_4_SERVER_ENTERPRISE 138 
#define  OSTYPE_WINDOWS_NT_4_SMS 137 
#define  OSTYPE_WINDOWS_NT_4_WORKSTATION 136 
#define  OSTYPE_WINDOWS_SERVER_10 135 
#define  OSTYPE_WINDOWS_SERVER_11 134 
#define  OSTYPE_WINDOWS_SERVER_2008_R2 133 
#define  OSTYPE_WINDOWS_SERVER_8 132 
#define  OSTYPE_WINDOWS_SERVER_81 131 
#define  OSTYPE_WINDOWS_UNKNOWN 130 
#define  OSTYPE_WINDOWS_XP_HOME 129 
#define  OSTYPE_WINDOWS_XP_PROFESSIONAL 128 

char *OsTypeToStr(UINT type)
{
	switch (type)
	{
	case 0:
		return "Unsupported OS by SoftEther VPN\0\n";
	case OSTYPE_WINDOWS_95:
		return "Windows 95\0\n";
	case OSTYPE_WINDOWS_98:
		return "Windows 98\0\n";
	case OSTYPE_WINDOWS_ME:
		return "Windows Millennium Edition\0\n";
	case OSTYPE_WINDOWS_UNKNOWN:
		return "Windows 9x Unknown Version\0\n";
	case OSTYPE_WINDOWS_NT_4_WORKSTATION:
		return "Windows NT 4.0 Workstation\0\n";
	case OSTYPE_WINDOWS_NT_4_SERVER:
		return "Windows NT 4.0 Server\0\n";
	case OSTYPE_WINDOWS_NT_4_SERVER_ENTERPRISE:
		return "Windows NT 4.0 Server, Enterprise Edition\0\n";
	case OSTYPE_WINDOWS_NT_4_BACKOFFICE:
		return "BackOffice Server 4.5\0\n";
	case OSTYPE_WINDOWS_NT_4_SMS:
		return "Small Business Server 4.5\0\n";
	case OSTYPE_WINDOWS_2000_PROFESSIONAL:
		return "Windows 2000 Professional\0\n";
	case OSTYPE_WINDOWS_2000_SERVER:
		return "Windows 2000 Server\0\n";
	case OSTYPE_WINDOWS_2000_ADVANCED_SERVER:
		return "Windows 2000 Advanced Server\0\n";
	case OSTYPE_WINDOWS_2000_DATACENTER_SERVER:
		return "Windows 2000 Datacenter Server\0\n";
	case OSTYPE_WINDOWS_2000_BACKOFFICE:
		return "BackOffice Server 2000\0\n";
	case OSTYPE_WINDOWS_2000_SBS:
		return "Small Business Server 2000\0\n";
	case OSTYPE_WINDOWS_XP_HOME:
		return "Windows XP Home Edition\0\n";
	case OSTYPE_WINDOWS_XP_PROFESSIONAL:
		return "Windows XP Professional\0\n";
	case OSTYPE_WINDOWS_2003_WEB:
		return "Windows Server 2003 Web Edition\0\n";
	case OSTYPE_WINDOWS_2003_STANDARD:
		return "Windows Server 2003 Standard Edition\0\n";
	case OSTYPE_WINDOWS_2003_ENTERPRISE:
		return "Windows Server 2003 Enterprise Edition\0\n";
	case OSTYPE_WINDOWS_2003_DATACENTER:
		return "Windows Server 2003 Datacenter Edition\0\n";
	case OSTYPE_WINDOWS_2003_BACKOFFICE:
		return "BackOffice Server 2003\0\n";
	case OSTYPE_WINDOWS_2003_SBS:
		return "Small Business Server 2003\0\n";
	case OSTYPE_WINDOWS_LONGHORN_PROFESSIONAL:
		return "Windows Vista\0\n";
	case OSTYPE_WINDOWS_LONGHORN_SERVER:
		return "Windows Server 2008\0\n";
	case OSTYPE_WINDOWS_7:
		return "Windows 7\0\n";
	case OSTYPE_WINDOWS_SERVER_2008_R2:
		return "Windows Server 2008 R2\0\n";
	case OSTYPE_WINDOWS_8:
		return "Windows 8\0\n";
	case OSTYPE_WINDOWS_SERVER_8:
		return "Windows Server 2012\0\n";
	case OSTYPE_WINDOWS_81:
		return "Windows 8.1\0\n";
	case OSTYPE_WINDOWS_SERVER_81:
		return "Windows Server 2012 R2\0\n";
	case OSTYPE_WINDOWS_10:
		return "Windows 10\0\n";
	case OSTYPE_WINDOWS_SERVER_10:
		return "Windows Server 2016\0\n";
	case OSTYPE_WINDOWS_11:
		return "Newer than Windows 10\0\n";
	case OSTYPE_WINDOWS_SERVER_11:
		return "Newer than Windows Server 2016\0\n";
	case OSTYPE_UNIX_UNKNOWN:
		return "UNIX System\0\n";
	case OSTYPE_LINUX:
		return "Linux\0\n";
	case OSTYPE_SOLARIS:
		return "Sun Solaris\0\n";
	case OSTYPE_CYGWIN:
		return "Gnu Cygwin\0\n";
	case OSTYPE_BSD:
		return "BSD System\0\n";
	case OSTYPE_MACOS_X:
		return "Mac OS X\0\n";
	}

	return "Unknown OS";
}