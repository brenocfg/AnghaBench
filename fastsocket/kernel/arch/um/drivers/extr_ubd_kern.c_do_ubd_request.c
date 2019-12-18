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
struct ubd {scalar_t__ end_sg; scalar_t__ start_sg; struct request* request; int /*<<< orphan*/  restart; struct scatterlist* sg; } ;
struct scatterlist {int length; int /*<<< orphan*/  offset; } ;
struct request_queue {struct ubd* queuedata; } ;
struct request {int dummy; } ;
struct io_thread_req {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 scalar_t__ blk_rq_map_sg (struct request_queue*,struct request*,struct scatterlist*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  kfree (struct io_thread_req*) ; 
 struct io_thread_req* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int os_write_file (int /*<<< orphan*/ ,struct io_thread_req**,int) ; 
 int /*<<< orphan*/  prepare_request (struct request*,struct io_thread_req*,unsigned long long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  restart ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  thread_fd ; 

__attribute__((used)) static void do_ubd_request(struct request_queue *q)
{
	struct io_thread_req *io_req;
	struct request *req;
	sector_t sector;
	int n;

	while(1){
		struct ubd *dev = q->queuedata;
		if(dev->end_sg == 0){
			struct request *req = blk_fetch_request(q);
			if(req == NULL)
				return;

			dev->request = req;
			dev->start_sg = 0;
			dev->end_sg = blk_rq_map_sg(q, req, dev->sg);
		}

		req = dev->request;
		sector = blk_rq_pos(req);
		while(dev->start_sg < dev->end_sg){
			struct scatterlist *sg = &dev->sg[dev->start_sg];

			io_req = kmalloc(sizeof(struct io_thread_req),
					 GFP_ATOMIC);
			if(io_req == NULL){
				if(list_empty(&dev->restart))
					list_add(&dev->restart, &restart);
				return;
			}
			prepare_request(req, io_req,
					(unsigned long long)sector << 9,
					sg->offset, sg->length, sg_page(sg));

			sector += sg->length >> 9;
			n = os_write_file(thread_fd, &io_req,
					  sizeof(struct io_thread_req *));
			if(n != sizeof(struct io_thread_req *)){
				if(n != -EAGAIN)
					printk("write to io thread failed, "
					       "errno = %d\n", -n);
				else if(list_empty(&dev->restart))
					list_add(&dev->restart, &restart);
				kfree(io_req);
				return;
			}

			dev->start_sg++;
		}
		dev->end_sg = 0;
		dev->request = NULL;
	}
}