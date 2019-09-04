#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* priv_data; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_6__ {int /*<<< orphan*/  ca_file; } ;
struct TYPE_8__ {int /*<<< orphan*/  ca_array; TYPE_1__ tls_shared; } ;
typedef  TYPE_3__ TLSContext ;
typedef  int /*<<< orphan*/ * CFArrayRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRetain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int import_pem (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int load_ca(URLContext *h)
{
    TLSContext *c = h->priv_data;
    int ret = 0;
    CFArrayRef array = NULL;

    if ((ret = import_pem(h, c->tls_shared.ca_file, &array)) < 0)
        goto end;

    if (!(c->ca_array = CFRetain(array))) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

end:
    if (array)
        CFRelease(array);
    return ret;
}