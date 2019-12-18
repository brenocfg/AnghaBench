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
struct nv50_curs {int dummy; } ;
struct nv50_chan {int /*<<< orphan*/  user; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 struct nv50_chan* nv50_chan (struct nv50_curs*) ; 
 struct nv50_curs* nv50_curs (struct drm_crtc*) ; 
 int /*<<< orphan*/  nv_wo32 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
nv50_crtc_cursor_move(struct drm_crtc *crtc, int x, int y)
{
	struct nv50_curs *curs = nv50_curs(crtc);
	struct nv50_chan *chan = nv50_chan(curs);
	nv_wo32(chan->user, 0x0084, (y << 16) | (x & 0xffff));
	nv_wo32(chan->user, 0x0080, 0x00000000);
	return 0;
}