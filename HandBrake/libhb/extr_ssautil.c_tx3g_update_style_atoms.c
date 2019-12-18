#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int flags; int fg_rgb; int fg_alpha; } ;
struct TYPE_7__ {int* buf; } ;
struct TYPE_6__ {int style_atom_count; int style_start; double height; TYPE_1__ out_style; TYPE_4__ style_atoms; } ;
typedef  TYPE_2__ hb_tx3g_style_context_t ;

/* Variables and functions */
 int HB_STYLE_FLAG_BOLD ; 
 int HB_STYLE_FLAG_ITALIC ; 
 int HB_STYLE_FLAG_UNDERLINE ; 
 int /*<<< orphan*/  check_realloc_output (TYPE_4__*,int) ; 

__attribute__((used)) static int tx3g_update_style_atoms(hb_tx3g_style_context_t *ctx, int stop)
{
    uint8_t * style_entry;
    uint8_t   face = 0;
    int       font_size;
    int       pos  = 10 + (12 * ctx->style_atom_count);
    int       size = 10 + (12 * (ctx->style_atom_count + 1));

    if (!check_realloc_output(&ctx->style_atoms, size))
    {
        return 0;
    }
    style_entry = ctx->style_atoms.buf + pos;

    if (ctx->out_style.flags & HB_STYLE_FLAG_BOLD)
        face |= 1;
    if (ctx->out_style.flags & HB_STYLE_FLAG_ITALIC)
        face |= 2;
    if (ctx->out_style.flags & HB_STYLE_FLAG_UNDERLINE)
        face |= 4;

    style_entry[0]  = (ctx->style_start >> 8) & 0xff;   // startChar
    style_entry[1]  = ctx->style_start & 0xff;
    style_entry[2]  = (stop >> 8) & 0xff;               // endChar
    style_entry[3]  = stop & 0xff;
    style_entry[4]  = 0;            // font-ID msb
    style_entry[5]  = 1;            // font-ID lsb
    style_entry[6]  = face;         // face-style-flags
    font_size       = 0.05 * ctx->height;
    if (font_size < 12)
    {
        font_size = 12;
    }
    else if (font_size > 255)
    {
        font_size = 255;
    }
    style_entry[7]  = font_size;    // font-size
    style_entry[8]  = (ctx->out_style.fg_rgb >> 16) & 0xff; // r
    style_entry[9]  = (ctx->out_style.fg_rgb >> 8)  & 0xff; // g
    style_entry[10] = (ctx->out_style.fg_rgb)       & 0xff; // b
    style_entry[11] = ctx->out_style.fg_alpha;              // a

    ctx->style_atom_count++;

    return 1;
}