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
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_3__ {char* za_name; int za_num_integers; int za_integer_length; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  dump_zap_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  umem_free (void*,int) ; 
 void* umem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,void*) ; 

__attribute__((used)) static void
dump_zap(objset_t *os, uint64_t object, void *data, size_t size)
{
	zap_cursor_t zc;
	zap_attribute_t attr;
	void *prop;
	unsigned i;

	dump_zap_stats(os, object);
	(void) printf("\n");

	for (zap_cursor_init(&zc, os, object);
	    zap_cursor_retrieve(&zc, &attr) == 0;
	    zap_cursor_advance(&zc)) {
		(void) printf("\t\t%s = ", attr.za_name);
		if (attr.za_num_integers == 0) {
			(void) printf("\n");
			continue;
		}
		prop = umem_zalloc(attr.za_num_integers *
		    attr.za_integer_length, UMEM_NOFAIL);
		(void) zap_lookup(os, object, attr.za_name,
		    attr.za_integer_length, attr.za_num_integers, prop);
		if (attr.za_integer_length == 1) {
			(void) printf("%s", (char *)prop);
		} else {
			for (i = 0; i < attr.za_num_integers; i++) {
				switch (attr.za_integer_length) {
				case 2:
					(void) printf("%u ",
					    ((uint16_t *)prop)[i]);
					break;
				case 4:
					(void) printf("%u ",
					    ((uint32_t *)prop)[i]);
					break;
				case 8:
					(void) printf("%lld ",
					    (u_longlong_t)((int64_t *)prop)[i]);
					break;
				}
			}
		}
		(void) printf("\n");
		umem_free(prop, attr.za_num_integers * attr.za_integer_length);
	}
	zap_cursor_fini(&zc);
}