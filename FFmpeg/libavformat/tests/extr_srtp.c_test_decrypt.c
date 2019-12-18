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
typedef  int /*<<< orphan*/  uint8_t ;
struct SRTPContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_srtp_decrypt (struct SRTPContext*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  print_data (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int test_decrypt(struct SRTPContext *srtp, const uint8_t *in, int len,
                        uint8_t *out)
{
    memcpy(out, in, len);
    if (!ff_srtp_decrypt(srtp, out, &len)) {
        print_data(out, len);
        return len;
    } else
        return -1;
}