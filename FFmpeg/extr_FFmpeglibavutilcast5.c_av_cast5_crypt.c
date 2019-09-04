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
typedef  int /*<<< orphan*/  AVCAST5 ;

/* Variables and functions */
 int /*<<< orphan*/  decipher (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encipher (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void av_cast5_crypt(AVCAST5* cs, uint8_t* dst, const uint8_t* src, int count, int decrypt)
{
    while (count--) {
        if (decrypt){
            decipher(cs, dst, src, NULL);
        } else {
            encipher(cs, dst, src);
        }
        src = src + 8;
        dst = dst + 8;
    }
}