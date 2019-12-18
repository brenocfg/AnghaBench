#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ qid7; scalar_t__ idx3; } ;
union cvmx_pko_reg_queue_ptrs1 {scalar_t__ u64; TYPE_1__ s; } ;
struct TYPE_4__ {int tail; int static_p; int static_q; int s_tail; int qos_mask; int /*<<< orphan*/  buf_ptr; scalar_t__ queue; scalar_t__ port; scalar_t__ index; } ;
union cvmx_pko_mem_queue_ptrs {scalar_t__ u64; TYPE_2__ s; } ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  cvmx_pko_status_t ;
typedef  int cvmx_cmd_queue_result_t ;

/* Variables and functions */
#define  CVMX_CMD_QUEUE_ALREADY_SETUP 131 
#define  CVMX_CMD_QUEUE_INVALID_PARAM 130 
#define  CVMX_CMD_QUEUE_NO_MEMORY 129 
 int /*<<< orphan*/  CVMX_CMD_QUEUE_PKO (scalar_t__) ; 
 int CVMX_CMD_QUEUE_SUCCESS ; 
 int /*<<< orphan*/  CVMX_FPA_OUTPUT_BUFFER_POOL ; 
 scalar_t__ CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE ; 
 int /*<<< orphan*/  CVMX_PKO_CMD_QUEUE_INIT_ERROR ; 
 int CVMX_PKO_COMMAND_BUFFER_SIZE_ADJUST ; 
 int /*<<< orphan*/  CVMX_PKO_INVALID_PORT ; 
 int /*<<< orphan*/  CVMX_PKO_INVALID_PRIORITY ; 
 int /*<<< orphan*/  CVMX_PKO_INVALID_QUEUE ; 
 scalar_t__ CVMX_PKO_MAX_OUTPUT_QUEUES ; 
 int /*<<< orphan*/  CVMX_PKO_MAX_QUEUE_DEPTH ; 
 int /*<<< orphan*/  CVMX_PKO_MEM_QUEUE_PTRS ; 
 scalar_t__ CVMX_PKO_MEM_QUEUE_PTRS_ILLEGAL_PID ; 
 int /*<<< orphan*/  CVMX_PKO_NO_MEMORY ; 
 scalar_t__ CVMX_PKO_NUM_OUTPUT_PORTS ; 
 int /*<<< orphan*/  CVMX_PKO_PORT_ALREADY_SETUP ; 
 int /*<<< orphan*/  CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 ; 
 int /*<<< orphan*/  CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 ; 
#define  CVMX_PKO_QUEUE_STATIC_PRIORITY 128 
 int /*<<< orphan*/  CVMX_PKO_REG_QUEUE_PTRS1 ; 
 int /*<<< orphan*/  CVMX_PKO_SUCCESS ; 
 int /*<<< orphan*/  CVMX_SYNCWS ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 int /*<<< orphan*/  OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_cmd_queue_buffer (int /*<<< orphan*/ ) ; 
 int cvmx_cmd_queue_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 int /*<<< orphan*/  cvmx_octeon_is_pass1 () ; 
 int /*<<< orphan*/  cvmx_ptr_to_phys (scalar_t__*) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

cvmx_pko_status_t cvmx_pko_config_port(uint64_t port, uint64_t base_queue,
				       uint64_t num_queues,
				       const uint64_t priority[])
{
	cvmx_pko_status_t result_code;
	uint64_t queue;
	union cvmx_pko_mem_queue_ptrs config;
	union cvmx_pko_reg_queue_ptrs1 config1;
	int static_priority_base = -1;
	int static_priority_end = -1;

	if ((port >= CVMX_PKO_NUM_OUTPUT_PORTS)
	    && (port != CVMX_PKO_MEM_QUEUE_PTRS_ILLEGAL_PID)) {
		cvmx_dprintf("ERROR: cvmx_pko_config_port: Invalid port %llu\n",
			     (unsigned long long)port);
		return CVMX_PKO_INVALID_PORT;
	}

	if (base_queue + num_queues > CVMX_PKO_MAX_OUTPUT_QUEUES) {
		cvmx_dprintf
		    ("ERROR: cvmx_pko_config_port: Invalid queue range %llu\n",
		     (unsigned long long)(base_queue + num_queues));
		return CVMX_PKO_INVALID_QUEUE;
	}

	if (port != CVMX_PKO_MEM_QUEUE_PTRS_ILLEGAL_PID) {
		/*
		 * Validate the static queue priority setup and set
		 * static_priority_base and static_priority_end
		 * accordingly.
		 */
		for (queue = 0; queue < num_queues; queue++) {
			/* Find first queue of static priority */
			if (static_priority_base == -1
			    && priority[queue] ==
			    CVMX_PKO_QUEUE_STATIC_PRIORITY)
				static_priority_base = queue;
			/* Find last queue of static priority */
			if (static_priority_base != -1
			    && static_priority_end == -1
			    && priority[queue] != CVMX_PKO_QUEUE_STATIC_PRIORITY
			    && queue)
				static_priority_end = queue - 1;
			else if (static_priority_base != -1
				 && static_priority_end == -1
				 && queue == num_queues - 1)
				/* all queues are static priority */
				static_priority_end = queue;
			/*
			 * Check to make sure all static priority
			 * queues are contiguous.  Also catches some
			 * cases of static priorites not starting at
			 * queue 0.
			 */
			if (static_priority_end != -1
			    && (int)queue > static_priority_end
			    && priority[queue] ==
			    CVMX_PKO_QUEUE_STATIC_PRIORITY) {
				cvmx_dprintf("ERROR: cvmx_pko_config_port: "
					     "Static priority queues aren't "
					     "contiguous or don't start at "
					     "base queue. q: %d, eq: %d\n",
					(int)queue, static_priority_end);
				return CVMX_PKO_INVALID_PRIORITY;
			}
		}
		if (static_priority_base > 0) {
			cvmx_dprintf("ERROR: cvmx_pko_config_port: Static "
				     "priority queues don't start at base "
				     "queue. sq: %d\n",
				static_priority_base);
			return CVMX_PKO_INVALID_PRIORITY;
		}
#if 0
		cvmx_dprintf("Port %d: Static priority queue base: %d, "
			     "end: %d\n", port,
			static_priority_base, static_priority_end);
#endif
	}
	/*
	 * At this point, static_priority_base and static_priority_end
	 * are either both -1, or are valid start/end queue
	 * numbers.
	 */

	result_code = CVMX_PKO_SUCCESS;

#ifdef PKO_DEBUG
	cvmx_dprintf("num queues: %d (%lld,%lld)\n", num_queues,
		     CVMX_PKO_QUEUES_PER_PORT_INTERFACE0,
		     CVMX_PKO_QUEUES_PER_PORT_INTERFACE1);
#endif

	for (queue = 0; queue < num_queues; queue++) {
		uint64_t *buf_ptr = NULL;

		config1.u64 = 0;
		config1.s.idx3 = queue >> 3;
		config1.s.qid7 = (base_queue + queue) >> 7;

		config.u64 = 0;
		config.s.tail = queue == (num_queues - 1);
		config.s.index = queue;
		config.s.port = port;
		config.s.queue = base_queue + queue;

		if (!cvmx_octeon_is_pass1()) {
			config.s.static_p = static_priority_base >= 0;
			config.s.static_q = (int)queue <= static_priority_end;
			config.s.s_tail = (int)queue == static_priority_end;
		}
		/*
		 * Convert the priority into an enable bit field. Try
		 * to space the bits out evenly so the packet don't
		 * get grouped up
		 */
		switch ((int)priority[queue]) {
		case 0:
			config.s.qos_mask = 0x00;
			break;
		case 1:
			config.s.qos_mask = 0x01;
			break;
		case 2:
			config.s.qos_mask = 0x11;
			break;
		case 3:
			config.s.qos_mask = 0x49;
			break;
		case 4:
			config.s.qos_mask = 0x55;
			break;
		case 5:
			config.s.qos_mask = 0x57;
			break;
		case 6:
			config.s.qos_mask = 0x77;
			break;
		case 7:
			config.s.qos_mask = 0x7f;
			break;
		case 8:
			config.s.qos_mask = 0xff;
			break;
		case CVMX_PKO_QUEUE_STATIC_PRIORITY:
			/* Pass 1 will fall through to the error case */
			if (!cvmx_octeon_is_pass1()) {
				config.s.qos_mask = 0xff;
				break;
			}
		default:
			cvmx_dprintf("ERROR: cvmx_pko_config_port: Invalid "
				     "priority %llu\n",
				(unsigned long long)priority[queue]);
			config.s.qos_mask = 0xff;
			result_code = CVMX_PKO_INVALID_PRIORITY;
			break;
		}

		if (port != CVMX_PKO_MEM_QUEUE_PTRS_ILLEGAL_PID) {
			cvmx_cmd_queue_result_t cmd_res =
			    cvmx_cmd_queue_initialize(CVMX_CMD_QUEUE_PKO
						      (base_queue + queue),
						      CVMX_PKO_MAX_QUEUE_DEPTH,
						      CVMX_FPA_OUTPUT_BUFFER_POOL,
						      CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE
						      -
						      CVMX_PKO_COMMAND_BUFFER_SIZE_ADJUST
						      * 8);
			if (cmd_res != CVMX_CMD_QUEUE_SUCCESS) {
				switch (cmd_res) {
				case CVMX_CMD_QUEUE_NO_MEMORY:
					cvmx_dprintf("ERROR: "
						     "cvmx_pko_config_port: "
						     "Unable to allocate "
						     "output buffer.\n");
					return CVMX_PKO_NO_MEMORY;
				case CVMX_CMD_QUEUE_ALREADY_SETUP:
					cvmx_dprintf
					    ("ERROR: cvmx_pko_config_port: Port already setup.\n");
					return CVMX_PKO_PORT_ALREADY_SETUP;
				case CVMX_CMD_QUEUE_INVALID_PARAM:
				default:
					cvmx_dprintf
					    ("ERROR: cvmx_pko_config_port: Command queue initialization failed.\n");
					return CVMX_PKO_CMD_QUEUE_INIT_ERROR;
				}
			}

			buf_ptr =
			    (uint64_t *)
			    cvmx_cmd_queue_buffer(CVMX_CMD_QUEUE_PKO
						  (base_queue + queue));
			config.s.buf_ptr = cvmx_ptr_to_phys(buf_ptr);
		} else
			config.s.buf_ptr = 0;

		CVMX_SYNCWS;

		if (!OCTEON_IS_MODEL(OCTEON_CN3XXX))
			cvmx_write_csr(CVMX_PKO_REG_QUEUE_PTRS1, config1.u64);
		cvmx_write_csr(CVMX_PKO_MEM_QUEUE_PTRS, config.u64);
	}

	return result_code;
}