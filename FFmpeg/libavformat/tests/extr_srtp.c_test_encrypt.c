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
struct SRTPContext {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int RTP_MAX_PACKET_LENGTH ; 
 int /*<<< orphan*/  ff_srtp_decrypt (struct SRTPContext*,char*,int*) ; 
 int ff_srtp_encrypt (struct SRTPContext*,int /*<<< orphan*/  const*,int,char*,int) ; 
 int /*<<< orphan*/  ff_srtp_free (struct SRTPContext*) ; 
 int /*<<< orphan*/  ff_srtp_set_crypto (struct SRTPContext*,char const*,char const*) ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void test_encrypt(const uint8_t *data, int in_len, const char *suite,
                         const char *key)
{
    struct SRTPContext enc = { 0 }, dec = { 0 };
    int len;
    char buf[RTP_MAX_PACKET_LENGTH];
    ff_srtp_set_crypto(&enc, suite, key);
    ff_srtp_set_crypto(&dec, suite, key);
    len = ff_srtp_encrypt(&enc, data, in_len, buf, sizeof(buf));
    if (!ff_srtp_decrypt(&dec, buf, &len)) {
        if (len == in_len && !memcmp(buf, data, len))
            printf("Decrypted content matches input\n");
        else
            printf("Decrypted content doesn't match input\n");
    } else {
        printf("Decryption failed\n");
    }
    ff_srtp_free(&enc);
    ff_srtp_free(&dec);
}