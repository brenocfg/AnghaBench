void z80_unused_port_w(unsigned int port, unsigned char data)
{
#if LOGERROR
  error("Z80 unused write to port %04X = %02X (%x)\n", port, data, Z80.pc.w.l);
#endif
}