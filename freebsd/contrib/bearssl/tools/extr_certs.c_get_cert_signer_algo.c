#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  br_x509_decoder_context ;
struct TYPE_3__ {int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ br_x509_certificate ;

/* Variables and functions */
 int br_x509_decoder_get_signer_key_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_x509_decoder_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int br_x509_decoder_last_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_x509_decoder_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int
get_cert_signer_algo(br_x509_certificate *xc)
{
	br_x509_decoder_context dc;
	int err;

	br_x509_decoder_init(&dc, 0, 0);
	br_x509_decoder_push(&dc, xc->data, xc->data_len);
	err = br_x509_decoder_last_error(&dc);
	if (err != 0) {
		fprintf(stderr,
			"ERROR: certificate decoding failed with error %d\n",
			-err);
		return 0;
	}
	return br_x509_decoder_get_signer_key_type(&dc);
}