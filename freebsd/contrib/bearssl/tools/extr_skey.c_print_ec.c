#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * pk8pem; int /*<<< orphan*/ * pk8der; int /*<<< orphan*/ * rawpem; int /*<<< orphan*/ * rawder; scalar_t__ print_C; scalar_t__ print_text; } ;
typedef  TYPE_1__ outspec ;
typedef  int /*<<< orphan*/  br_ec_public_key ;
struct TYPE_9__ {int curve; int /*<<< orphan*/  xlen; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ br_ec_private_key ;

/* Variables and functions */
 int BR_EC_KBUF_PUB_MAX_SIZE ; 
 scalar_t__ br_ec_compute_pub (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  br_ec_get_default () ; 
 size_t br_encode_ec_pkcs8_der (unsigned char*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 size_t br_encode_ec_raw_der (unsigned char*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_int_C (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_int_text (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int write_to_file (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int write_to_pem_file (int /*<<< orphan*/ *,unsigned char*,size_t,char*) ; 
 int /*<<< orphan*/  xfree (unsigned char*) ; 
 unsigned char* xmalloc (size_t) ; 

__attribute__((used)) static int
print_ec(const br_ec_private_key *sk, outspec *os)
{
	br_ec_public_key pk;
	unsigned kbuf[BR_EC_KBUF_PUB_MAX_SIZE];
	unsigned char *buf;
	size_t len;
	int r;

	if (os->print_text) {
		print_int_text("x", sk->x, sk->xlen);
	}
	if (os->print_C) {
		print_int_C("EC_X", sk->x, sk->xlen);
		printf("\nstatic const br_ec_private_key EC = {\n");
		printf("\t%d,\n", sk->curve);
		printf("\t(unsigned char *)EC_X, sizeof EC_X\n");
		printf("};\n");
	}

	if (os->rawder == NULL && os->rawpem == NULL
		&& os->pk8der == NULL && os->pk8pem == NULL)
	{
		return 1;
	}
	if (br_ec_compute_pub(br_ec_get_default(), &pk, kbuf, sk) == 0) {
		fprintf(stderr,
			"ERROR: cannot re-encode (unsupported curve)\n");
		return 0;
	}

	r = 1;
	if (os->rawder != NULL || os->rawpem != NULL) {
		len = br_encode_ec_raw_der(NULL, sk, &pk);
		if (len == 0) {
			fprintf(stderr, "ERROR: cannot re-encode"
				" (unsupported curve)\n");
			return 0;
		}
		buf = xmalloc(len);
		if (br_encode_ec_raw_der(buf, sk, &pk) != len) {
			fprintf(stderr, "ERROR: re-encode failure\n");
			xfree(buf);
			return 0;
		}
		if (os->rawder != NULL) {
			r &= write_to_file(os->rawder, buf, len);
		}
		if (os->rawpem != NULL) {
			r &= write_to_pem_file(os->rawpem,
				buf, len, "EC PRIVATE KEY");
		}
		xfree(buf);
	}
	if (os->pk8der != NULL || os->pk8pem != NULL) {
		len = br_encode_ec_pkcs8_der(NULL, sk, &pk);
		if (len == 0) {
			fprintf(stderr, "ERROR: cannot re-encode"
				" (unsupported curve)\n");
			return 0;
		}
		buf = xmalloc(len);
		if (br_encode_ec_pkcs8_der(buf, sk, &pk) != len) {
			fprintf(stderr, "ERROR: re-encode failure\n");
			xfree(buf);
			return 0;
		}
		if (os->pk8der != NULL) {
			r &= write_to_file(os->pk8der, buf, len);
		}
		if (os->pk8pem != NULL) {
			r &= write_to_pem_file(os->pk8pem,
				buf, len, "PRIVATE KEY");
		}
		xfree(buf);
	}
	return r;
}