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
struct ssl_primary_config {int /*<<< orphan*/  pinned_key; int /*<<< orphan*/  cipher_list13; int /*<<< orphan*/  cipher_list; int /*<<< orphan*/  egdsocket; int /*<<< orphan*/  random_file; int /*<<< orphan*/  clientcert; int /*<<< orphan*/  CAfile; int /*<<< orphan*/  CApath; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 

void Curl_free_primary_ssl_config(struct ssl_primary_config* sslc)
{
  Curl_safefree(sslc->CApath);
  Curl_safefree(sslc->CAfile);
  Curl_safefree(sslc->clientcert);
  Curl_safefree(sslc->random_file);
  Curl_safefree(sslc->egdsocket);
  Curl_safefree(sslc->cipher_list);
  Curl_safefree(sslc->cipher_list13);
  Curl_safefree(sslc->pinned_key);
}