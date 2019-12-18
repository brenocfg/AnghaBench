#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ucontext_t ;
struct sigaction {int sa_flags; int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_mask; } ;
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_2__ {int /*<<< orphan*/  pidfile; scalar_t__ daemonize; int /*<<< orphan*/  assert_line; int /*<<< orphan*/  assert_file; int /*<<< orphan*/  assert_failed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISQUE_VERSION ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int SA_NODEFER ; 
 int SA_ONSTACK ; 
 int SA_RESETHAND ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioKillThreads () ; 
 int /*<<< orphan*/  bugReportStart () ; 
 int /*<<< orphan*/  dictGetHashFunctionSeed () ; 
 int /*<<< orphan*/  genDisqueInfoString (char*) ; 
 int /*<<< orphan*/  getAllClientsInfoString () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  logCurrentClient () ; 
 int /*<<< orphan*/  logRegisters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logStackTrace (int /*<<< orphan*/ *) ; 
 scalar_t__ memtest_test_linux_anonymous_maps () ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  serverLogRaw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
    ucontext_t *uc = (ucontext_t*) secret;
    sds infostring, clients;
    struct sigaction act;
    UNUSED(info);

    bugReportStart();
    serverLog(LL_WARNING,
        "    Disque %s crashed by signal: %d", DISQUE_VERSION, sig);
    serverLog(LL_WARNING,
        "    Failed assertion: %s (%s:%d)", server.assert_failed,
                        server.assert_file, server.assert_line);

    /* Log the stack trace */
    serverLog(LL_WARNING, "--- STACK TRACE");
    logStackTrace(uc);

    /* Log INFO and CLIENT LIST */
    serverLog(LL_WARNING, "--- INFO OUTPUT");
    infostring = genDisqueInfoString("all");
    infostring = sdscatprintf(infostring, "hash_init_value: %u\n",
        dictGetHashFunctionSeed());
    serverLogRaw(LL_WARNING, infostring);
    serverLog(LL_WARNING, "--- CLIENT LIST OUTPUT");
    clients = getAllClientsInfoString();
    serverLogRaw(LL_WARNING, clients);
    sdsfree(infostring);
    sdsfree(clients);

    /* Log the current client */
    logCurrentClient();

    /* Log dump of processor registers */
    logRegisters(uc);

#if defined(HAVE_PROC_MAPS)
    /* Test memory */
    serverLog(LL_WARNING, "--- FAST MEMORY TEST");
    bioKillThreads();
    if (memtest_test_linux_anonymous_maps()) {
        serverLog(LL_WARNING,
            "!!! MEMORY ERROR DETECTED! Check your memory ASAP !!!");
    } else {
        serverLog(LL_WARNING,
            "Fast memory test PASSED, however your memory can still be broken. Please run a memory test for several hours if possible.");
    }
#endif

    serverLog(LL_WARNING,
"\n=== DISQUE BUG REPORT END. Make sure to include from START to END. ===\n\n"
"       Please report the crash by opening an issue on github:\n\n"
"           http://github.com/antirez/disque/issues\n\n"
"  Suspect RAM error? Use disque-server --test-memory to verify it.\n\n"
);
    /* free(messages); Don't call free() with possibly corrupted memory. */
    if (server.daemonize) unlink(server.pidfile);

    /* Make sure we exit with the right signal at the end. So for instance
     * the core will be dumped if enabled. */
    sigemptyset (&act.sa_mask);
    act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND;
    act.sa_handler = SIG_DFL;
    sigaction (sig, &act, NULL);
    kill(getpid(),sig);
}