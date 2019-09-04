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
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 unsigned long long b64_ntop (int /*<<< orphan*/  const*,size_t,char*,size_t) ; 
 int /*<<< orphan*/  handler_emsg (char*) ; 
 int /*<<< orphan*/  htons (unsigned long long) ; 

int encode_hybi(u_char const *src, size_t srclength,
                char *target, size_t targsize, unsigned int opcode)
{
    unsigned long long b64_sz, len_offset = 1, payload_offset = 2, len = 0;
    
    if ((int)srclength <= 0)
    {
        return 0;
    }

    b64_sz = ((srclength - 1) / 3) * 4 + 4;

    target[0] = (char)(opcode & 0x0F | 0x80);

    if (b64_sz <= 125) {
        target[1] = (char) b64_sz;
        payload_offset = 2;
    } else if ((b64_sz > 125) && (b64_sz < 65536)) {
        target[1] = (char) 126;
        *(u_short*)&(target[2]) = htons(b64_sz);
        payload_offset = 4;
    } else {
        handler_emsg("Sending frames larger than 65535 bytes not supported\n");
        return -1;
        //target[1] = (char) 127;
        //*(u_long*)&(target[2]) = htonl(b64_sz);
        //payload_offset = 10;
    }

    len = b64_ntop(src, srclength, target+payload_offset, targsize-payload_offset);
    
    if (len < 0) {
        return len;
    }

    return len + payload_offset;
}