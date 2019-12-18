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
struct s_write {unsigned char* enc_buffer; int enc_buffer_capacity; int new_sentence; int new_channel; scalar_t__ last_scr_sequence; scalar_t__ last_pts; int /*<<< orphan*/  list; scalar_t__ in_xds_mode; scalar_t__ subline; } ;

/* Variables and functions */
 int INITIAL_ENC_BUFFER_CAPACITY ; 
 int /*<<< orphan*/  hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static int general_608_init (struct s_write *wb)
{
    if( !wb->enc_buffer )
    {
        wb->enc_buffer=(unsigned char *) malloc (INITIAL_ENC_BUFFER_CAPACITY);
        if (wb->enc_buffer==NULL)
            return -1;
        wb->enc_buffer_capacity=INITIAL_ENC_BUFFER_CAPACITY;
    }

    if( !wb->subline) {
        wb->subline = malloc(2048);

        if (!wb->subline)
        {
            return -1;
        }
    }

    wb->new_sentence = 1;
    wb->new_channel = 1;
    wb->in_xds_mode = 0;

    hb_buffer_list_clear(&wb->list);
    wb->last_pts = 0;
    wb->last_scr_sequence = 0;
    return 0;
}