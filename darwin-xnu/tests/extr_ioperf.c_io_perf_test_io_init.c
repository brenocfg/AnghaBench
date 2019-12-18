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
struct sched_param {int /*<<< orphan*/  sched_priority; } ;

/* Variables and functions */
 int FILE_SIZE ; 
 int /*<<< orphan*/  F_NOCACHE ; 
 int /*<<< orphan*/  IOPOL_IMPORTANT ; 
 int /*<<< orphan*/  IOPOL_SCOPE_PROCESS ; 
 int /*<<< orphan*/  IOPOL_TYPE_DISK ; 
 int IO_SIZE ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  THR_MANAGER_PRI ; 
 int /*<<< orphan*/  T_ASSERT_GE_INT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_NOTNULL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*,...) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_PASS (char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_SKIP (char*) ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  data_buf ; 
 int /*<<< orphan*/  environ ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int posix_spawn (int*,char* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_setschedparam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 scalar_t__ read (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setiopolicy_np (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync () ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
io_perf_test_io_init(void)
{
    int spawn_ret, pid;
    char *const mount_args[] = {"/usr/local/sbin/mount_nand.sh", NULL};
    spawn_ret = posix_spawn(&pid, mount_args[0], NULL, NULL, mount_args, environ);
    if (spawn_ret < 0) {
	T_SKIP("NAND mounting in LTE not possible on this device. Skipping test!");
    }
    waitpid(pid, &spawn_ret, 0);
    if (WIFEXITED(spawn_ret) && !WEXITSTATUS(spawn_ret)) {
        T_PASS("NAND mounted successfully");
    } else {
        T_SKIP("Unable to mount NAND. Skipping test!");
    }

    /* Mark the main thread as fixed priority */
    struct sched_param param = {.sched_priority = THR_MANAGER_PRI};
    T_ASSERT_POSIX_ZERO(pthread_setschedparam(pthread_self(), SCHED_FIFO, &param),
            "pthread_setschedparam");

    /* Set I/O Policy to Tier 0 */
    T_ASSERT_POSIX_ZERO(setiopolicy_np(IOPOL_TYPE_DISK, IOPOL_SCOPE_PROCESS,
            IOPOL_IMPORTANT), "setiopolicy");

    /* Create data buffer */
    data_buf = malloc(IO_SIZE * 16);
    T_ASSERT_NOTNULL(data_buf, "Data buffer allocation");

    int rndfd = open("/dev/urandom", O_RDONLY, S_IRUSR);
    T_ASSERT_POSIX_SUCCESS(rndfd, "Open /dev/urandom");
    T_ASSERT_GE_INT((int)read(rndfd, data_buf, IO_SIZE * 16), 0, "read /dev/urandom");
    close(rndfd);

    /* Create test file */
    int fd = open("/mnt2/test", O_CREAT | O_WRONLY, S_IRUSR);
    T_ASSERT_POSIX_SUCCESS(fd, 0, "Open /mnt2/test for writing!");

    T_ASSERT_POSIX_ZERO(fcntl(fd, F_NOCACHE, 1), "fcntl F_NOCACHE enable");
    for (int size = 0; size < FILE_SIZE;) {
        T_QUIET;
        T_ASSERT_GE_INT((int)write(fd, data_buf, IO_SIZE * 16), 0, "write test file");
        size += (IO_SIZE * 16);
    }
    close(fd);
    sync();

}