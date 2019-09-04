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
struct ccdigest_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIPSPOST_TRACE_EVENT ; 
 int /*<<< orphan*/  cchmac_di_clear (struct ccdigest_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cchmac_di_decl (struct ccdigest_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cchmac_final (struct ccdigest_info const*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  cchmac_init (struct ccdigest_info const*,int /*<<< orphan*/ ,size_t,void const*) ; 
 int /*<<< orphan*/  cchmac_update (struct ccdigest_info const*,int /*<<< orphan*/ ,size_t,void const*) ; 
 int /*<<< orphan*/  hc ; 

void cchmac(const struct ccdigest_info *di,
            size_t key_len, const void *key,
            size_t data_len, const void *data, unsigned char *mac) {
    FIPSPOST_TRACE_EVENT;

    cchmac_di_decl(di, hc);
    cchmac_init(di, hc, key_len, key);
    cchmac_update(di, hc, data_len, data);
    cchmac_final(di, hc, mac);
	cchmac_di_clear(di, hc);
}