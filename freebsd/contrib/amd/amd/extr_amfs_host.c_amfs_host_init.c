#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_4__ {scalar_t__ mf_server; int /*<<< orphan*/  mf_info; } ;
typedef  TYPE_1__ mntfs ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  get_mntfs_wchan (TYPE_1__*) ; 
 int /*<<< orphan*/  get_mountd_port (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int
amfs_host_init(mntfs *mf)
{
  u_short mountd_port;

  if (strchr(mf->mf_info, ':') == 0)
    return ENOENT;

  /*
   * This is primarily to schedule a wakeup so that as soon
   * as our fileserver is ready, we can continue setting up
   * the host filesystem.  If we don't do this, the standard
   * amfs_auto code will set up a fileserver structure, but it will
   * have to wait for another nfs request from the client to come
   * in before finishing.  Our way is faster since we don't have
   * to wait for the client to resend its request (which could
   * take a second or two).
   */
  /*
   * First, we find the fileserver for this mntfs and then call
   * get_mountd_port with our mntfs passed as the wait channel.
   * get_mountd_port will check some things and then schedule
   * it so that when the fileserver is ready, a wakeup is done
   * on this mntfs.   amfs_cont() is already sleeping on this mntfs
   * so as soon as that wakeup happens amfs_cont() is called and
   * this mount is retried.
   */
  if (mf->mf_server)
    /*
     * We don't really care if there's an error returned.
     * Since this is just to help speed things along, the
     * error will get handled properly elsewhere.
     */
    get_mountd_port(mf->mf_server, &mountd_port, get_mntfs_wchan(mf));

  return 0;
}