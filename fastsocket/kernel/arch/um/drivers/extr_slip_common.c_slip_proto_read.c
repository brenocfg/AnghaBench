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
struct slip_proto {int more; size_t pos; int /*<<< orphan*/ * ibuf; int /*<<< orphan*/  esc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int net_read (int,int /*<<< orphan*/ *,int) ; 
 int slip_unesc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 

int slip_proto_read(int fd, void *buf, int len, struct slip_proto *slip)
{
	int i, n, size, start;

	if(slip->more > 0){
		i = 0;
		while(i < slip->more){
			size = slip_unesc(slip->ibuf[i++], slip->ibuf,
					  &slip->pos, &slip->esc);
			if(size){
				memcpy(buf, slip->ibuf, size);
				memmove(slip->ibuf, &slip->ibuf[i],
					slip->more - i);
				slip->more = slip->more - i;
				return size;
			}
		}
		slip->more = 0;
	}

	n = net_read(fd, &slip->ibuf[slip->pos],
		     sizeof(slip->ibuf) - slip->pos);
	if(n <= 0)
		return n;

	start = slip->pos;
	for(i = 0; i < n; i++){
		size = slip_unesc(slip->ibuf[start + i], slip->ibuf,&slip->pos,
				  &slip->esc);
		if(size){
			memcpy(buf, slip->ibuf, size);
			memmove(slip->ibuf, &slip->ibuf[start+i+1],
				n - (i + 1));
			slip->more = n - (i + 1);
			return size;
		}
	}
	return 0;
}