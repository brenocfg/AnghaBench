#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  UID ;
struct TYPE_2__ {int /*<<< orphan*/  source_container_ul; } ;
typedef  TYPE_1__ MXFCryptoContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ IS_KLV_KEY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxf_crypto_source_container_ul ; 

__attribute__((used)) static int mxf_read_cryptographic_context(void *arg, AVIOContext *pb, int tag, int size, UID uid, int64_t klv_offset)
{
    MXFCryptoContext *cryptocontext = arg;
    if (size != 16)
        return AVERROR_INVALIDDATA;
    if (IS_KLV_KEY(uid, mxf_crypto_source_container_ul))
        avio_read(pb, cryptocontext->source_container_ul, 16);
    return 0;
}