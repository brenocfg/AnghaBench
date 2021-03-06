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
typedef  int /*<<< orphan*/  network_mysqld_type_t ;
typedef  int /*<<< orphan*/  guint8 ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 scalar_t__ network_mysqld_proto_append_int8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ network_mysqld_type_get_double (int /*<<< orphan*/ *,double*) ; 

__attribute__((used)) static int network_mysqld_proto_binary_append_double_type(GString *packet, network_mysqld_type_t *type) {
	union {
		double d;
		guint8 d_char_shadow[sizeof(double)];
	} double_copy;
	int err = 0;
	unsigned long i;

	err = err || network_mysqld_type_get_double(type, &double_copy.d);
	if (0 != err) return -1;

#ifdef WORDS_BIGENDIAN
	/* big endian: ppc, ... */
	for (i = 0; 0 == err && i < sizeof(double); i++) {
		err = err || network_mysqld_proto_append_int8(packet, double_copy.d_char_shadow[sizeof(double) - 1 - i]);
	}
#else
	/* little endian: x86: network == system byte-order */
	for (i = 0; 0 == err && i < sizeof(double); i++) {
		err = err || network_mysqld_proto_append_int8(packet, double_copy.d_char_shadow[i]);
	}
#endif

	return err ? -1 : 0;
}