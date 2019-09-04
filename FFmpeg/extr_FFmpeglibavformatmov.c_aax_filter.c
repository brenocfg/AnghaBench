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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  aes_decrypt; int /*<<< orphan*/  file_key; int /*<<< orphan*/  file_iv; } ;
typedef  TYPE_1__ MOVContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_aes_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned char*,int) ; 
 int /*<<< orphan*/  av_aes_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aax_filter(uint8_t *input, int size, MOVContext *c)
{
    int blocks = 0;
    unsigned char iv[16];

    memcpy(iv, c->file_iv, 16); // iv is overwritten
    blocks = size >> 4; // trailing bytes are not encrypted!
    av_aes_init(c->aes_decrypt, c->file_key, 128, 1);
    av_aes_crypt(c->aes_decrypt, input, input, blocks, iv, 1);

    return 0;
}