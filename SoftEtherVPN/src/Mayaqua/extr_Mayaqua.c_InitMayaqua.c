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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  Alert (char*,char*) ; 
 int /*<<< orphan*/  AlertW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckEndian () ; 
 int /*<<< orphan*/  CheckUnixTempDir () ; 
 int /*<<< orphan*/ * CopyStr (char*) ; 
 int /*<<< orphan*/  GetCurrentMachineIpProcessHash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetExeNameW (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  InitCommandLineStr (int,char**) ; 
 int /*<<< orphan*/  InitCrc32 () ; 
 int /*<<< orphan*/  InitCryptLibrary () ; 
 int /*<<< orphan*/  InitFifo () ; 
 int /*<<< orphan*/  InitGetExeName (char*) ; 
 int /*<<< orphan*/  InitHamcore () ; 
 int /*<<< orphan*/  InitKernelStatus () ; 
 int /*<<< orphan*/  InitNetwork () ; 
 int /*<<< orphan*/  InitOsInfo () ; 
 int /*<<< orphan*/  InitProbe () ; 
 int /*<<< orphan*/  InitProcessCallOnce () ; 
 int /*<<< orphan*/  InitSecure () ; 
 int /*<<< orphan*/  InitStringLibrary () ; 
 int /*<<< orphan*/  InitTable () ; 
 int /*<<< orphan*/  InitThreading () ; 
 int /*<<< orphan*/  InitTick64 () ; 
 int /*<<< orphan*/  InitTracking () ; 
 int IsFileExistsW (int /*<<< orphan*/ *) ; 
 scalar_t__ IsTrackingEnabled () ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LoadPrivateIPFile () ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MsInit () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  OSInit () ; 
 int OSIsSupportedOs () ; 
 int RsaCheckEx () ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SetLocale (int /*<<< orphan*/ *) ; 
 scalar_t__ StrCmpi (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ SystemTime64 () ; 
 int /*<<< orphan*/  UNIX_SVC_ARG_FOREGROUND ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Win32IsNt () ; 
 int /*<<< orphan*/  _DISABLE_PER_THREAD_LOCALE ; 
 int /*<<< orphan*/  _configthreadlocale (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmdline ; 
 int dot_net_mode ; 
 int /*<<< orphan*/ * exename ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int g_debug ; 
 int g_foreground ; 
 int g_memcheck ; 
 int /*<<< orphan*/  init_mayaqua_counter ; 
 int /*<<< orphan*/  is_nt ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tick_manual_lock ; 

void InitMayaqua(bool memcheck, bool debug, int argc, char **argv)
{
	wchar_t tmp[MAX_PATH];
	UCHAR hash[SHA1_SIZE];

	if ((init_mayaqua_counter++) > 0)
	{
		return;
	}

	InitProcessCallOnce();

	g_memcheck = memcheck;
	g_debug = debug;
	cmdline = NULL;
	if (dot_net_mode == false)
	{
		// Fail this for some reason when this is called this in .NET mode
		setbuf(stdout, NULL);
	}

#ifdef OS_UNIX
	g_foreground = (argc >= 3 && StrCmpi(argv[2], UNIX_SVC_ARG_FOREGROUND) == 0);
#else
	g_foreground = false;
#endif // OS_UNIX

	// Acquisition whether NT
#ifdef	OS_WIN32
	is_nt = Win32IsNt();
#endif	// OS_WIN32

	// Check endian
	CheckEndian();

#ifdef	OS_WIN32
	_configthreadlocale(_DISABLE_PER_THREAD_LOCALE);
#endif	// OS_WIN32

	// Set the locale information of the CRT to the Japanese
	setlocale(LC_ALL, "");

	// Initialization of OS
	OSInit();

	// Initialize the random number
	srand((UINT)SystemTime64());

	tick_manual_lock = NewLock();

	// Initialization of CRC32
	InitCrc32();

	// Initialization of the FIFO system
	InitFifo();

	// Initialize the Kernel status
	InitKernelStatus();

	if (IsTrackingEnabled())
	{
		// Initialize the tracking
		InitTracking();
	}

	// Initialization of thread pool
	InitThreading();

	// Initialize the string library
	InitStringLibrary();

	// Initialization of the locale information
	SetLocale(NULL);

	// Initialization of the crypt library
	InitCryptLibrary();

	// Initialization of the real-time clock
	InitTick64();

	// Initialize the network communication module
	InitNetwork();

	// Initialization of the acquisition of the EXE file name
	InitGetExeName(argc >= 1 ? argv[0] : NULL);

	// Initialization of the command line string
	InitCommandLineStr(argc, argv);

	// Initialization of OS information
	InitOsInfo();

	// Initialization of the operating system-specific module
#ifdef	OS_WIN32
	MsInit();	// Microsoft Win32
#endif	// OS_WIN32

	// Initialization of the security token module
	InitSecure();

	if (OSIsSupportedOs() == false)
	{
		// Abort
		exit(0);
	}

	// RSA Check
	if (RsaCheckEx() == false)
	{
		// Abort
		Alert("OpenSSL Library Init Failed. (too old?)\nPlease install the latest version of OpenSSL.\n\n", "RsaCheck()");
		exit(0);
	}

	// Initialization of HamCore file system
	InitHamcore();

	// Initialization of string table routine
	InitTable();

	if (exename == NULL)
	{
		// Executable file name
		exename = CopyStr("unknown");
	}

	// Check whether the executable file name of themselves is found
	// (If not found, quit because this is started in strange path)
	GetExeNameW(tmp, sizeof(tmp));
	if (IsFileExistsW(tmp) == false)
	{
		wchar_t tmp2[MAX_SIZE];

		UniFormat(tmp2, sizeof(tmp2),
			L"Error: Executable binary file \"%s\" not found.\r\n\r\n"
			L"Please execute program with full path.\r\n",
			tmp);

		AlertW(tmp2, NULL);
		_exit(0);
	}

	CheckUnixTempDir();

	// Initialization of Probe
	InitProbe();

	// Initialization of Machine Hash
	GetCurrentMachineIpProcessHash(hash);

	// Reading Private IP file
	LoadPrivateIPFile();
}