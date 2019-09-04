#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  desc ;
struct TYPE_4__ {int index; int /*<<< orphan*/ * texture; } ;
typedef  int /*<<< orphan*/  ID3D11Texture2D ;
typedef  TYPE_1__ AVD3D11FrameDescriptor ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11Texture2D_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  free_texture ; 

__attribute__((used)) static AVBufferRef *wrap_texture_buf(ID3D11Texture2D *tex, int index)
{
    AVBufferRef *buf;
    AVD3D11FrameDescriptor *desc = av_mallocz(sizeof(*desc));
    if (!desc) {
        ID3D11Texture2D_Release(tex);
        return NULL;
    }

    desc->texture = tex;
    desc->index   = index;

    buf = av_buffer_create((uint8_t *)desc, sizeof(desc), free_texture, tex, 0);
    if (!buf) {
        ID3D11Texture2D_Release(tex);
        av_free(desc);
        return NULL;
    }

    return buf;
}