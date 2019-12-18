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
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  const* bytestream; int /*<<< orphan*/  const* bytestream_end; } ;
typedef  TYPE_1__ PNMContext ;

/* Variables and functions */
 int /*<<< orphan*/  pnm_space (int) ; 

__attribute__((used)) static void pnm_get(PNMContext *sc, char *str, int buf_size)
{
    char *s;
    int c;
    uint8_t *bs  = sc->bytestream;
    const uint8_t *end = sc->bytestream_end;

    /* skip spaces and comments */
    while (bs < end) {
        c = *bs++;
        if (c == '#')  {
            while (c != '\n' && bs < end) {
                c = *bs++;
            }
        } else if (!pnm_space(c)) {
            break;
        }
    }

    s = str;
    while (bs < end && !pnm_space(c) && (s - str) < buf_size - 1) {
        *s++ = c;
        c = *bs++;
    }
    *s = '\0';
    sc->bytestream = bs;
}