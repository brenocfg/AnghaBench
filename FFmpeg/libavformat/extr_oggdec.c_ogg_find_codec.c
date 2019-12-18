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
struct ogg_codec {int magicsize; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct ogg_codec const** ogg_codecs ; 

__attribute__((used)) static const struct ogg_codec *ogg_find_codec(uint8_t *buf, int size)
{
    int i;

    for (i = 0; ogg_codecs[i]; i++)
        if (size >= ogg_codecs[i]->magicsize &&
            !memcmp(buf, ogg_codecs[i]->magic, ogg_codecs[i]->magicsize))
            return ogg_codecs[i];

    return NULL;
}