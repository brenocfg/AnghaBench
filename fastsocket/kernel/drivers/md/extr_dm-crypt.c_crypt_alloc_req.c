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
struct crypt_config {scalar_t__ req; int /*<<< orphan*/  tfm; int /*<<< orphan*/  req_pool; } ;
struct convert_context {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  ablkcipher_request_set_callback (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ablkcipher_request_set_tfm (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmreq_of_req (struct crypt_config*,scalar_t__) ; 
 int /*<<< orphan*/  kcryptd_async_done ; 
 scalar_t__ mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypt_alloc_req(struct crypt_config *cc,
			    struct convert_context *ctx)
{
	if (!cc->req)
		cc->req = mempool_alloc(cc->req_pool, GFP_NOIO);
	ablkcipher_request_set_tfm(cc->req, cc->tfm);
	ablkcipher_request_set_callback(cc->req, CRYPTO_TFM_REQ_MAY_BACKLOG |
					CRYPTO_TFM_REQ_MAY_SLEEP,
					kcryptd_async_done,
					dmreq_of_req(cc, cc->req));
}