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
struct s_write {TYPE_1__* data608; } ;
struct TYPE_2__ {scalar_t__ channel; } ;

/* Variables and functions */
 scalar_t__ cc_channel ; 
 scalar_t__ debug_608 ; 
 int /*<<< orphan*/  hb_log (char*,unsigned char const,unsigned char const,unsigned char) ; 
 int /*<<< orphan*/  write_char (unsigned char,struct s_write*) ; 

__attribute__((used)) static void handle_double(const unsigned char c1, const unsigned char c2,
                          struct s_write *wb)
{
    unsigned char c;
    if (wb->data608->channel!=cc_channel)
        return;
    if (c2>=0x30 && c2<=0x3f)
    {
        c=c2 + 0x50; // So if c>=0x80 && c<=0x8f, it comes from here
        if (debug_608)
            hb_log ("\rDouble: %02X %02X  -->  %c\n",c1,c2,c);
        write_char(c,wb);
    }
}