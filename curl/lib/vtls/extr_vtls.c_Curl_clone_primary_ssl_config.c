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
struct ssl_primary_config {int /*<<< orphan*/  sessionid; int /*<<< orphan*/  verifystatus; int /*<<< orphan*/  verifyhost; int /*<<< orphan*/  verifypeer; int /*<<< orphan*/  version_max; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAfile ; 
 int /*<<< orphan*/  CApath ; 
 int /*<<< orphan*/  CLONE_STRING (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  cipher_list ; 
 int /*<<< orphan*/  cipher_list13 ; 
 int /*<<< orphan*/  clientcert ; 
 int /*<<< orphan*/  egdsocket ; 
 int /*<<< orphan*/  pinned_key ; 
 int /*<<< orphan*/  random_file ; 

bool
Curl_clone_primary_ssl_config(struct ssl_primary_config *source,
                              struct ssl_primary_config *dest)
{
  dest->version = source->version;
  dest->version_max = source->version_max;
  dest->verifypeer = source->verifypeer;
  dest->verifyhost = source->verifyhost;
  dest->verifystatus = source->verifystatus;
  dest->sessionid = source->sessionid;

  CLONE_STRING(CApath);
  CLONE_STRING(CAfile);
  CLONE_STRING(clientcert);
  CLONE_STRING(random_file);
  CLONE_STRING(egdsocket);
  CLONE_STRING(cipher_list);
  CLONE_STRING(cipher_list13);
  CLONE_STRING(pinned_key);

  return TRUE;
}