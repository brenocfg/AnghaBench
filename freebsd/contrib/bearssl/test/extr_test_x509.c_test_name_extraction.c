#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_18__ {int* dp_stack; int* rp_stack; TYPE_3__* vtable; } ;
typedef  TYPE_1__ br_x509_minimal_context ;
struct TYPE_19__ {unsigned char* oid; scalar_t__* buf; int len; scalar_t__ status; } ;
typedef  TYPE_2__ br_name_element ;
struct TYPE_22__ {int id; int /*<<< orphan*/  impl; } ;
struct TYPE_21__ {int num; scalar_t__ status; int /*<<< orphan*/ * expected; } ;
struct TYPE_20__ {unsigned int (* end_chain ) (TYPE_3__**) ;int /*<<< orphan*/  (* end_cert ) (TYPE_3__**) ;int /*<<< orphan*/  (* append ) (TYPE_3__**,unsigned char*,size_t) ;int /*<<< orphan*/  (* start_cert ) (TYPE_3__**,size_t) ;int /*<<< orphan*/  (* start_chain ) (TYPE_3__**,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 unsigned int BR_ERR_X509_NOT_TRUSTED ; 
 int /*<<< orphan*/  DEFAULT_TIME ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  br_ec_get_default () ; 
 int /*<<< orphan*/  br_ecdsa_vrfy_asn1_get_default () ; 
 int /*<<< orphan*/  br_rsa_pkcs1_vrfy_get_default () ; 
 int /*<<< orphan*/  br_sha256_vtable ; 
 int /*<<< orphan*/  br_x509_minimal_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_x509_minimal_set_ecdsa (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_x509_minimal_set_hash (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_x509_minimal_set_name_elements (TYPE_1__*,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  br_x509_minimal_set_rsa (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_x509_minimal_set_time (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  free_name_elements (TYPE_2__*,size_t) ; 
 TYPE_9__* hash_impls ; 
 size_t max_dp_usage ; 
 size_t max_rp_usage ; 
 TYPE_8__* names_ref ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned char* read_file (char*,size_t*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_to_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__**,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__**) ; 
 unsigned int stub5 (TYPE_3__**) ; 
 int /*<<< orphan*/  xfree (unsigned char*) ; 
 void* xmalloc (int) ; 

__attribute__((used)) static void
test_name_extraction(void)
{
	unsigned char *data;
	size_t len;
	br_x509_minimal_context ctx;
	uint32_t days, seconds;
	size_t u;
	unsigned status;
	br_name_element *names;
	size_t num_names;
	int good;

	printf("Name extraction: ");
	fflush(stdout);
	data = read_file("names.crt", &len);
	br_x509_minimal_init(&ctx, &br_sha256_vtable, NULL, 0);
	for (u = 0; hash_impls[u].id; u ++) {
		int id;

		id = hash_impls[u].id;
		br_x509_minimal_set_hash(&ctx, id, hash_impls[u].impl);
	}
	br_x509_minimal_set_rsa(&ctx, br_rsa_pkcs1_vrfy_get_default());
	br_x509_minimal_set_ecdsa(&ctx,
		br_ec_get_default(), br_ecdsa_vrfy_asn1_get_default());
	string_to_time(DEFAULT_TIME, &days, &seconds);
	br_x509_minimal_set_time(&ctx, days, seconds);

	num_names = (sizeof names_ref) / (sizeof names_ref[0]);
	names = xmalloc(num_names * sizeof *names);
	for (u = 0; u < num_names; u ++) {
		int num;
		unsigned char *oid;

		num = names_ref[u].num;
		if (num > 0) {
			oid = xmalloc(5);
			oid[0] = 4;
			oid[1] = 0x29;
			oid[2] = 0x01;
			oid[3] = 0x01;
			oid[4] = num;
		} else if (num == 0) {
			oid = xmalloc(13);
			oid[0] = 0x00;
			oid[1] = 0x00;
			oid[2] = 0x0A;
			oid[3] = 0x2B;
			oid[4] = 0x06;
			oid[5] = 0x01;
			oid[6] = 0x04;
			oid[7] = 0x01;
			oid[8] = 0x82;
			oid[9] = 0x37;
			oid[10] = 0x14;
			oid[11] = 0x02;
			oid[12] = 0x03;
		} else {
			oid = xmalloc(2);
			oid[0] = 0x00;
			oid[1] = -num;
		}
		names[u].oid = oid;
		names[u].buf = xmalloc(256);
		names[u].len = 256;
	}
	br_x509_minimal_set_name_elements(&ctx, names, num_names);

	/*
	 * Put "canaries" to detect actual stack usage.
	 */
	for (u = 0; u < (sizeof ctx.dp_stack) / sizeof(uint32_t); u ++) {
		ctx.dp_stack[u] = 0xA7C083FE;
	}
	for (u = 0; u < (sizeof ctx.rp_stack) / sizeof(uint32_t); u ++) {
		ctx.rp_stack[u] = 0xA7C083FE;
	}

	/*
	 * Run the engine. Since we set no trust anchor, we expect a status
	 * of "not trusted".
	 */
	ctx.vtable->start_chain(&ctx.vtable, NULL);
	ctx.vtable->start_cert(&ctx.vtable, len);
	ctx.vtable->append(&ctx.vtable, data, len);
	ctx.vtable->end_cert(&ctx.vtable);
	status = ctx.vtable->end_chain(&ctx.vtable);
	if (status != BR_ERR_X509_NOT_TRUSTED) {
		fprintf(stderr, "wrong status: %u\n", status);
		exit(EXIT_FAILURE);
	}

	/*
	 * Check stack usage.
	 */
	for (u = (sizeof ctx.dp_stack) / sizeof(uint32_t); u > 0; u --) {
		if (ctx.dp_stack[u - 1] != 0xA7C083FE) {
			if (max_dp_usage < u) {
				max_dp_usage = u;
			}
			break;
		}
	}
	for (u = (sizeof ctx.rp_stack) / sizeof(uint32_t); u > 0; u --) {
		if (ctx.rp_stack[u - 1] != 0xA7C083FE) {
			if (max_rp_usage < u) {
				max_rp_usage = u;
			}
			break;
		}
	}

	good = 1;
	for (u = 0; u < num_names; u ++) {
		if (names[u].status != names_ref[u].status) {
			printf("ERR: name %u (id=%d): status=%d, expected=%d\n",
				(unsigned)u, names_ref[u].num,
				names[u].status, names_ref[u].status);
			if (names[u].status > 0) {
				unsigned char *p;

				printf("  obtained:");
				p = (unsigned char *)names[u].buf;
				while (*p) {
					printf(" %02X", *p ++);
				}
				printf("\n");
			}
			good = 0;
			continue;
		}
		if (names_ref[u].expected == NULL) {
			if (names[u].buf[0] != 0) {
				printf("ERR: name %u not zero-terminated\n",
					(unsigned)u);
				good = 0;
				continue;
			}
		} else {
			if (strcmp(names[u].buf, names_ref[u].expected) != 0) {
				unsigned char *p;

				printf("ERR: name %u (id=%d): wrong value\n",
					(unsigned)u, names_ref[u].num);
				printf("  expected:");
				p = (unsigned char *)names_ref[u].expected;
				while (*p) {
					printf(" %02X", *p ++);
				}
				printf("\n");
				printf("  obtained:");
				p = (unsigned char *)names[u].buf;
				while (*p) {
					printf(" %02X", *p ++);
				}
				printf("\n");
				good = 0;
				continue;
			}
		}
	}
	if (!good) {
		exit(EXIT_FAILURE);
	}

	/*
	for (u = 0; u < num_names; u ++) {
		printf("%u: (%d)", (unsigned)u, names[u].status);
		if (names[u].status > 0) {
			size_t v;

			for (v = 0; names[u].buf[v]; v ++) {
				printf(" %02x", names[u].buf[v]);
			}
		}
		printf("\n");
	}
	*/

	xfree(data);
	free_name_elements(names, num_names);
	printf("OK\n");
}