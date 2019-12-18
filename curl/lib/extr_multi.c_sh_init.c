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
struct curl_hash {int dummy; } ;

/* Variables and functions */
 int Curl_hash_init (struct curl_hash*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_key_compare ; 
 int /*<<< orphan*/  hash_fd ; 
 int /*<<< orphan*/  sh_freeentry ; 

__attribute__((used)) static int sh_init(struct curl_hash *hash, int hashsize)
{
  return Curl_hash_init(hash, hashsize, hash_fd, fd_key_compare,
                        sh_freeentry);
}